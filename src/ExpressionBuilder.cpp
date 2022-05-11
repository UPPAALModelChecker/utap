// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2018 Uppsala University and Aalborg University.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA
*/

#include "utap/ExpressionBuilder.hpp"

#include <vector>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstring>

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::string;
using std::map;

inline static bool isMITL(const expression_t& e)
{
    return (e.getKind() == MITLFORMULA || e.getKind() == MITLRELEASE || e.getKind() == MITLUNTIL ||
            e.getKind() == MITLCONJ || e.getKind() == MITLDISJ || e.getKind() == MITLNEXT || e.getKind() == MITLATOM ||
            e.getKind() == MITLEXISTS || e.getKind() == MITLFORALL);
}

inline static expression_t toMITLAtom(const expression_t& e) { return expression_t::createUnary(MITLATOM, e); }

void ExpressionBuilder::ExpressionFragments::pop(uint32_t n)
{
    assert(n <= size());
    while (n--)
        pop();
}

ExpressionBuilder::ExpressionBuilder(Document& doc): document{doc}
{
    pushFrame(document.getGlobals().frame);
    scalar_count = 0;
}

void ExpressionBuilder::addPosition(uint32_t position, uint32_t offset, uint32_t line, const std::string& path)
{
    document.addPosition(position, offset, line, path);
}

void ExpressionBuilder::handleError(const TypeException& ex) { document.addError(position, ex.what()); }

void ExpressionBuilder::handleWarning(const TypeException& ex) { document.addWarning(position, ex.what()); }

void ExpressionBuilder::pushFrame(frame_t frame) { frames.push(std::move(frame)); }

void ExpressionBuilder::popFrame() { frames.pop(); }

bool ExpressionBuilder::resolve(const std::string& name, symbol_t& uid) const
{
    assert(!frames.empty());
    return frames.top().resolve(name, uid);
}

ExpressionBuilder::ExpressionFragments& ExpressionBuilder::getExpressions() { return fragments; }

bool ExpressionBuilder::isType(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid)) {
        return false;
    }
    return uid.getType().getKind() == TYPEDEF;
}

expression_t ExpressionBuilder::makeConstant(int value) const { return expression_t::createConstant(value, position); }

expression_t ExpressionBuilder::makeConstant(double value) const { return expression_t::createDouble(value, position); }

type_t ExpressionBuilder::applyPrefix(PREFIX prefix, type_t type)
{
    switch (prefix) {
    case PREFIX_CONST: return type.createPrefix(CONSTANT, position);
    case PREFIX_SYSTEM_META:
        // Meta in the syntax corresponds to a static variable internally.
        // Internal "meta" variables correspond to state meta variables.
        return type.createPrefix(SYSTEM_META, position);
    case PREFIX_URGENT: return type.createPrefix(URGENT, position);
    case PREFIX_BROADCAST: return type.createPrefix(BROADCAST, position);
    case PREFIX_URGENT_BROADCAST: return type.createPrefix(URGENT, position).createPrefix(BROADCAST, position);
    case PREFIX_HYBRID: return type.createPrefix(HYBRID, position);
    default: return type;
    }
}

void ExpressionBuilder::typeDuplicate() { typeFragments.duplicate(); }

void ExpressionBuilder::typePop() { typeFragments.pop(); }

void ExpressionBuilder::typeBool(PREFIX prefix)
{
    type_t type = type_t::createPrimitive(Constants::BOOL, position);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeInt(PREFIX prefix)
{
    type_t type = type_t::createPrimitive(Constants::INT, position);
    if (prefix != PREFIX_CONST) {
        type = type_t::createRange(type, makeConstant(defaultIntMin), makeConstant(defaultIntMax), position);
    }
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeString(PREFIX prefix)
{
    if (prefix != PREFIX_CONST) {
        typeFragments.push(type_t::createPrimitive(VOID_TYPE));
        throw TypeException("$Strings_should_always_be_const");
    }
    type_t type = type_t::createPrimitive(Constants::STRING, position);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeDouble(PREFIX prefix)
{
    type_t type = type_t::createPrimitive(Constants::DOUBLE, position);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeBoundedInt(PREFIX prefix)
{
    type_t type = type_t::createPrimitive(Constants::INT, position);
    type = type_t::createRange(type, fragments[1], fragments[0], position);
    fragments.pop(2);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeChannel(PREFIX prefix)
{
    type_t type = type_t::createPrimitive(CHANNEL, position);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeClock(PREFIX prefix)
{
    type_t type = type_t::createPrimitive(CLOCK, position);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::typeVoid()
{
    type_t type = type_t::createPrimitive(VOID_TYPE, position);
    typeFragments.push(type);
}

static void collectDependencies(std::set<symbol_t>& dependencies, expression_t expr)
{
    std::set<symbol_t> symbols;
    expr.collectPossibleReads(symbols);
    while (!symbols.empty()) {
        symbol_t s = *symbols.begin();
        symbols.erase(s);
        if (dependencies.find(s) == dependencies.end()) {
            dependencies.insert(s);
            if (auto* data = s.getData(); data) {
                variable_t* v = static_cast<variable_t*>(data);
                v->expr.collectPossibleReads(symbols);
            }
        }
    }
}

void ExpressionBuilder::typeScalar(PREFIX prefix)
{
    expression_t lower, upper;

    exprNat(1);
    exprBinary(MINUS);
    upper = fragments[0];
    lower = makeConstant(0);
    fragments.pop();

    type_t type = type_t::createPrimitive(SCALAR, position);
    type = type_t::createRange(type, lower, upper, position);
    type = applyPrefix(prefix, type);

    string count = std::to_string(scalar_count++);

    type = type.createLabel(string("#scalarset") + count, position);

    if (currentTemplate) {
        /* Local scalar definitions are local to a particular process
         * - not to the template. Therefore we prefix it with the
         * template name and rename the template name to the process
         * name whenever evaluating a P.symbol expression (where P is
         * a processs). See exprDot().
         */
        type = type.createLabel(currentTemplate->uid.getName() + "::", position);

        /* There are restrictions on how the size of a scalar set is
         * given (may not depend on free process parameters).
         * Therefore mark all symbols in upper and those that they
         * depend on as restricted.
         */
        collectDependencies(currentTemplate->restricted, upper);
    }
    typeFragments.push(type);
}

void ExpressionBuilder::typeName(PREFIX prefix, const char* name)
{
    symbol_t uid;
    assert(resolve(name, uid));

    if (!resolve(name, uid) || uid.getType().getKind() != TYPEDEF) {
        typeFragments.push(type_t::createPrimitive(VOID_TYPE));
        throw TypeException("$Identifier_is_undeclared_or_not_a_type_name");
    }

    type_t type = uid.getType()[0];

    /* We create a label here such that we can track the
     * position. This is not needed for type checking (we only use
     * name equivalence for scalarset, and they have a name embedded
     * in the type, see typeScalar()).
     */
    type = type.createLabel(uid.getName(), position);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::exprTrue()
{
    expression_t expr = makeConstant(1);
    expr.setType(type_t::createPrimitive(Constants::BOOL));
    fragments.push(expr);
}

void ExpressionBuilder::exprFalse()
{
    expression_t expr = makeConstant(0);
    expr.setType(type_t::createPrimitive(Constants::BOOL));
    fragments.push(expr);
}

void ExpressionBuilder::exprDouble(double d)
{
    expression_t expr = expression_t::createDouble(d, position);
    expr.setType(type_t::createPrimitive(Constants::DOUBLE));
    fragments.push(expr);
}

void ExpressionBuilder::exprString(const char* name)
{
    auto newstring = std::string{name};
    // remove quotes:
    newstring.pop_back();
    newstring.erase(0, 1);
    expression_t expr = makeConstant((int)document.add_string_if_new(newstring));
    expr.setType(type_t::createPrimitive(Constants::STRING));
    fragments.push(expr);
}

void ExpressionBuilder::exprId(const char* name)
{
    symbol_t uid;

    if (!resolve(name, uid)) {
        exprFalse();
        throw UnknownIdentifierError(name);
    }

    fragments.push(expression_t::createIdentifier(uid, position));
}

void ExpressionBuilder::exprDeadlock() { fragments.push(expression_t::createDeadlock(position)); }

void ExpressionBuilder::exprNat(int32_t n) { fragments.push(makeConstant(n)); }

void ExpressionBuilder::exprCallBegin() {}

// expects n argument expressions on the stack
void ExpressionBuilder::exprCallEnd(uint32_t n)
{
    expression_t e;
    type_t type;
    instance_t* instance;

    /* n+1'th element from the top is the identifier.
     */
    expression_t id = fragments[n];

    /* Create vector of sub expressions: The first expression
     * evaluates to the function or processset. The remaining
     * expressions are the arguments.
     */
    vector<expression_t> expr;
    for (int i = n; i >= 0; i--) {
        expr.push_back(fragments[i]);
    }
    fragments.pop(n + 1);

    /* The expression we create depends on whether id is a
     * function or a processset.
     */
    switch (id.getType().getKind()) {
    case EXTERNAL_FUNCTION:
    case FUNCTION:
        if (expr.size() != id.getType().size()) {
            handleError(TypeException{"$Wrong_number_of_arguments"});
        }
        e = expression_t::createNary(id.getType().getKind() == FUNCTION ? FUNCALL : EFUNCALL, expr, position,
                                     id.getType()[0]);
        break;

    case PROCESSSET:
        if (expr.size() - 1 != id.getType().size()) {
            handleError(TypeException{"$Wrong_number_of_arguments"});
        }
        instance = static_cast<instance_t*>(id.getSymbol().getData());

        /* Process set lookups are represented as expressions indexing
         * into an array. To satisfy the type checker, we create a
         * type matching this structure.
         */
        type = type_t::createProcess(instance->templ->frame);
        for (size_t i = 0; i < instance->unbound; i++) {
            type = type_t::createArray(type, instance->parameters[instance->unbound - i - 1].getType());
        }

        /* Now create the expression. Each argument to the proces set
         * lookup is represented as an ARRAY expression.
         */
        e = id;
        e.setType(type);
        for (size_t i = 1; i < expr.size(); i++) {
            type = type.getSub();
            e = expression_t::createBinary(ARRAY, e, expr[i], position, type);
        }
        break;

    default:
        handleError(TypeException{"$Function_expected"});
        e = makeConstant(0);
        break;
    }

    fragments.push(e);
}

// 2 expr     // array[index]
void ExpressionBuilder::exprArray()
{
    // Pop sub-expressions
    expression_t var = fragments[1];
    expression_t index = fragments[0];
    fragments.pop(2);

    type_t element;
    type_t type = var.getType();
    if (type.isArray()) {
        element = type.getSub();
    } else {
        element = type_t();
    }

    fragments.push(expression_t::createBinary(ARRAY, var, index, position, element));
}

// 1 expr
void ExpressionBuilder::exprPostIncrement()
{
    fragments[0] = expression_t::createUnary(POSTINCREMENT, fragments[0], position);
}

void ExpressionBuilder::exprPreIncrement()
{
    fragments[0] = expression_t::createUnary(PREINCREMENT, fragments[0], position, fragments[0].getType());
}

void ExpressionBuilder::exprPostDecrement()  // 1 expr
{
    fragments[0] = expression_t::createUnary(POSTDECREMENT, fragments[0], position);
}

void ExpressionBuilder::exprPreDecrement()
{
    fragments[0] = expression_t::createUnary(PREDECREMENT, fragments[0], position, fragments[0].getType());
}

void ExpressionBuilder::exprBuiltinFunction1(kind_t kind)
{
    fragments[0] = expression_t::createUnary(kind, fragments[0], position);
}

void ExpressionBuilder::exprBuiltinFunction2(kind_t kind)
{
    expression_t lvalue = fragments[1];
    expression_t rvalue = fragments[0];
    fragments.pop(1);
    fragments[0] = expression_t::createBinary(kind, lvalue, rvalue, position, lvalue.getType());
}

void ExpressionBuilder::exprBuiltinFunction3(kind_t kind)
{
    expression_t value1 = fragments[2];
    expression_t value2 = fragments[1];
    expression_t value3 = fragments[0];
    fragments.pop(2);
    fragments[0] = expression_t::createTernary(kind, value1, value2, value3, position, value1.getType());
}

void ExpressionBuilder::exprAssignment(kind_t op)  // 2 expr
{
    expression_t lvalue = fragments[1];
    expression_t rvalue = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(op, lvalue, rvalue, position, lvalue.getType()));
}

void ExpressionBuilder::exprUnary(kind_t unaryop)  // 1 expr
{
    switch (unaryop) {
    case PLUS:
        /* Unary plus can be ignored */
        break;
    case MINUS:
        unaryop = UNARY_MINUS;
        /* Fall through! */
    default: fragments[0] = expression_t::createUnary(unaryop, fragments[0], position);
    }
}

void ExpressionBuilder::exprBinary(kind_t binaryop)  // 2 expr
{
    kind_t mitlop = (binaryop == AND ? MITLCONJ : MITLDISJ);
    kind_t op = binaryop;
    expression_t left = fragments[1];
    expression_t right = fragments[0];
    if (isMITL(left) || isMITL(right)) {
        op = mitlop;
        if (!(isMITL(left) && isMITL(right))) {
            if (isMITL(left)) {
                op = mitlop;
                right = toMITLAtom(right);
            } else if (isMITL(right)) {
                op = mitlop;
                left = toMITLAtom(left);
            }
        }
    }
    fragments.pop(2);
    fragments.push(expression_t::createBinary(op, left, right, position));
}

void ExpressionBuilder::exprNary(kind_t kind, uint32_t num)
{
    // Pop fields
    vector<expression_t> fields(num);
    for (uint32_t i = 0; i < num; i++) {
        fields[i] = fragments[num - 1 - i];
    }
    fragments.pop(num);

    // Create N-ary expression
    fragments.push(expression_t::createNary(kind, fields, position));
}

void ExpressionBuilder::exprScenario(const char* name)
{
    symbol_t uid;
    bool check [[maybe_unused]] = resolve(name, uid);
    assert(check);
    expression_t scen = expression_t::createIdentifier(uid);
    expression_t expr = expression_t::createUnary(SCENARIO, scen, position);
    fragments.push(expression_t::createUnary(SCENARIO, scen, position));
}

expression_t ExpressionBuilder::exprScenario()
{
    symbol_t uid;
    bool check [[maybe_unused]] = resolve(document.obsTA, uid);
    assert(check);
    expression_t obs = expression_t::createIdentifier(uid);  // std::cout << obs << std::endl;
    int32_t i = obs.getType().findIndexOf("lmin");
    expression_t left =
        expression_t::createDot(obs, i, position,
                                type_t::createPrimitive(Constants::BOOL));  // std::cout << left << std::endl;

    obs = expression_t::createIdentifier(uid);
    i = obs.getType().findIndexOf("lmax");
    expression_t right =
        expression_t::createDot(obs, i, position,
                                type_t::createPrimitive(Constants::BOOL));  // std::cout << right << std::endl;
    return expression_t::createBinary(SCENARIO2, left, right, position);
}

void ExpressionBuilder::exprTernary(kind_t ternaryop, bool firstMissing)  // 3 expr
{
    expression_t first = firstMissing ? makeConstant(1) : fragments[2];
    expression_t second = fragments[1];
    expression_t third = fragments[0];
    fragments.pop(firstMissing ? 2 : 3);
    fragments.push(expression_t::createTernary(ternaryop, first, second, third, position));
}

void ExpressionBuilder::exprInlineIf()
{
    expression_t c = fragments[2];
    expression_t t = fragments[1];
    expression_t e = fragments[0];
    fragments.pop(3);
    fragments.push(expression_t::createTernary(INLINEIF, c, t, e, position, t.getType()));
}

void ExpressionBuilder::exprComma()
{
    expression_t e1 = fragments[1];
    expression_t e2 = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(COMMA, e1, e2, position, e2.getType()));
}

void ExpressionBuilder::exprLocation()
{
    expression_t expr = fragments[0];
    type_t type = expr.getType();
    if (type.isProcess()) {
        // TODO: create a separate type for location expressions and get rid of magical constants
        // we use special max-value to denote this special "meta-variable"
        expr = expression_t::createDot(expr, std::numeric_limits<int32_t>::max(), position,
                                       type_t::createPrimitive(Constants::LOCATION_EXPR));
    } else {
        handleError(NotAProcessError(expr.toString(true)));
    }
    fragments[0] = expr;
}

void ExpressionBuilder::exprDot(const char* id)
{
    expression_t expr = fragments[0];
    type_t type = expr.getType();
    if (type.isRecord()) {
        int32_t i = type.findIndexOf(id);
        if (i == -1) {
            handleError(HasNoMemberError(id));
        } else {
            expr = expression_t::createDot(expr, i, position, type.getSub(i));
        }
    } else if (type.isProcess()) {
        symbol_t name = expr.getSymbol();
        auto* process = static_cast<instance_t*>(name.getData());
        int32_t i = type.findIndexOf(id);
        if (i == -1) {
            handleError(HasNoMemberError(id));
        } else if (type.getSub(i).isLocation()) {
            expr = expression_t::createDot(expr, i, position, type_t::createPrimitive(Constants::BOOL));
        } else {
            type = type.getSub(i).rename(process->templ->uid.getName() + "::", name.getName() + "::");
            for (const auto& [s, e] : process->mapping)
                type = type.subst(s, e);
            expr = expression_t::createDot(expr, i, position, type);
        }
    } else if (type.is(PROCESSVAR)) {
        symbol_t uid;
        // temporarily set the frame to that of its associated template
        if (dynamicFrames.find(expr.getSymbol().getName()) == dynamicFrames.end()) {
            throw UnknownIdentifierError(expr.getSymbol().getName());
        }
        pushFrame(dynamicFrames[expr.getSymbol().getName()]);

        if (!resolve(id, uid)) {
            exprFalse();
            throw UnknownIdentifierError(id);
        }
        popFrame();  // Remove that frame again
        expression_t identifier = expression_t::createIdentifier(uid, position);

        expr = (expression_t::createNary(
            DYNAMICEVAL, {identifier, expr}, position,
            identifier.getType().isLocation()
                ? type_t::createPrimitive(Constants::BOOL, position)
                : identifier.getType()));  // type_t::createPrimitive (Constants::BOOL,position)));
    } else {
        handleError(IsNotAStructError(expr.toString(true)));
    }
    fragments[0] = expr;
}

void ExpressionBuilder::exprForAllBegin(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (!type.is(CONSTANT)) {
        type = type.createPrefix(CONSTANT);
    }

    pushFrame(frame_t::createFrame(frames.top()));
    symbol_t symbol = frames.top().addSymbol(name, type, position);

    if (!type.isInteger() && !type.isScalar()) {
        handleError(TypeException{"$Quantifier_must_range_over_integer_or_scalar_set"});
    }
}

void ExpressionBuilder::exprForAllEnd(const char* name)
{
    /* Create the forall expression. The symbol is added as an identifier
     * expression as the first child. Notice that the frame is discarded
     * but the identifier expression will maintain a reference to the
     * symbol so it will not be deallocated.
     */
    fragments[0] = expression_t::createBinary(FORALL, expression_t::createIdentifier(frames.top()[0], position),
                                              fragments[0], position);
    popFrame();
}

void ExpressionBuilder::exprExistsBegin(const char* name) { exprForAllBegin(name); }

void ExpressionBuilder::exprExistsEnd(const char* name)
{
    /* Create the exists expression. The symbol is added as an identifier
     * expression as the first child. Notice that the frame is discarded
     * but the identifier expression will maintain a reference to the
     * symbol so it will not be deallocated.
     */
    fragments[0] = expression_t::createBinary(EXISTS, expression_t::createIdentifier(frames.top()[0], position),
                                              fragments[0], position);
    popFrame();
}

void ExpressionBuilder::exprSumBegin(const char* name) { exprForAllBegin(name); }

void ExpressionBuilder::exprSumEnd(const char* name)
{
    /* Create the sum expression. The symbol is added as an identifier
     * expression as the first child. Notice that the frame is discarded
     * but the identifier expression will maintain a reference to the
     * symbol so it will not be deallocated.
     */
    fragments[0] = expression_t::createBinary(SUM, expression_t::createIdentifier(frames.top()[0], position),
                                              fragments[0], position);
    popFrame();
}

void ExpressionBuilder::exprProbaQualitative(Constants::kind_t pathType, Constants::kind_t comp, double probBound)
{
    auto invert = (comp == LE);
    auto& boundTypeOrBoundedExpr = fragments[3];
    auto& bound = fragments[2];
    auto& runs = fragments[1];
    auto& predicate = fragments[0];

    auto args = std::vector<expression_t>{runs, boundTypeOrBoundedExpr, bound,
                                          invert ? expression_t::createUnary(NOT, predicate, position) : predicate,
                                          expression_t::createDouble(invert ? 1.0 - probBound : probBound, position)};

    fragments.pop(4);
    fragments.push(expression_t::createNary(
        invert ? (pathType == BOX ? PROBAMINDIAMOND : PROBAMINBOX) : (pathType == BOX ? PROBAMINBOX : PROBAMINDIAMOND),
        std::move(args), position));
}

void ExpressionBuilder::exprMinMaxExp(Constants::kind_t kind, PRICETYPE ptype, Constants::kind_t quant)
{
    if (quant != Constants::DIAMOND) {
        handleError(TypeException{"$Wrong_path_quantifier"});
    }

    auto boundVar = fragments[4];
    auto bound = fragments[3];
    auto discrete = fragments[2];
    auto cont = fragments[1];

    if (!discrete.isTrue() && !cont.isTrue()) {
        discrete.setType(type_t::createPrimitive(LIST, position));
        cont.setType(type_t::createPrimitive(LIST, position));
    }
    auto& control = fragments[0];
    expression_t price;
    expression_t level = makeConstant(0);
    size_t nb = 5;
    switch (ptype) {
    case TIMEPRICE:  // use time
        price = makeConstant(1);
        break;
    case EXPRPRICE:  // user-provided expression
        price = fragments[5];
        ++nb;
        break;
    case PROBAPRICE:  // use boolean expression
        price = control;
        break;
    default: handleError(TypeException{"$Unknown_price_type"});
    }

    assert(nb <= fragments.size());

    auto args = std::vector<expression_t>{boundVar, bound, control, price, level, discrete, cont};
    fragments.pop(nb);
    fragments.push(expression_t::createNary(kind, std::move(args), position));
}

void ExpressionBuilder::exprLoadStrategy()
{
    expression_t discrete = fragments[2];
    expression_t cont = fragments[1];
    expression_t strat = fragments[0];
    if (!discrete.isTrue() && !cont.isTrue()) {
        discrete.setType(type_t::createPrimitive(LIST, position));
        cont.setType(type_t::createPrimitive(LIST, position));
    }
    fragments.pop(3);
    fragments.push(expression_t::createTernary(LOAD_STRAT, strat, discrete, cont, position));
}

void ExpressionBuilder::exprSaveStrategy()
{
    fragments[0] = expression_t::createUnary(SAVE_STRAT, fragments[0], position);
}

void ExpressionBuilder::exprProbaQuantitative(Constants::kind_t pathType)
{
    auto& boundTypeOrBoundedExpr = fragments[4];
    auto& bound = fragments[3];
    auto& runs = fragments[2];
    auto& predicate = fragments[1];
    auto& untilCond = fragments[0];

    auto args = std::vector<expression_t>{runs, boundTypeOrBoundedExpr, bound, predicate, untilCond};
    fragments.pop(5);
    fragments.push(expression_t::createNary((pathType == BOX ? PROBABOX : PROBADIAMOND), std::move(args), position));
}

void ExpressionBuilder::exprProbaCompare(Constants::kind_t pathType1, Constants::kind_t pathType2)
{
    auto& boundTypeOrBoundedExpr1 = fragments[7];
    auto& bound1 = fragments[6];
    auto& runs1 = fragments[5];
    auto& predicate1 = fragments[4];

    auto& boundTypeOrBoundedExpr2 = fragments[3];
    auto& bound2 = fragments[2];
    auto& runs2 = fragments[1];
    auto& predicate2 = fragments[0];

    if (runs1.getValue() != -1 || runs2.getValue() != -1)
        throw TypeException("The number of runs is not supported in probability comparison");

    auto args = std::vector<expression_t>{boundTypeOrBoundedExpr1, bound1, makeConstant(pathType1), predicate1,
                                          boundTypeOrBoundedExpr2, bound2, makeConstant(pathType2), predicate2};

    fragments.pop(8);
    fragments.push(expression_t::createNary(PROBACMP, std::move(args), position));
}

void ExpressionBuilder::exprProbaExpected(const char* aggregatingOp)
{
    auto& boundTypeOrBoundedExpr = fragments[3];
    auto& bound = fragments[2];
    auto& runs = fragments[1];
    auto& expression = fragments[0];

    if (runs.getKind() == CONSTANT && runs.getType().isInteger() && runs.getValue() < 0)
        runs = makeConstant(2);

    int aggOpId;
    if (strcmp("min", aggregatingOp) == 0)
        aggOpId = 0;
    else if (strcmp("max", aggregatingOp) == 0)
        aggOpId = 1;
    else
        throw TypeException("min or max expected");
    // TODO: add "acc" when the semantics is defined.

    auto args = std::vector<expression_t>{runs, boundTypeOrBoundedExpr, bound, makeConstant(aggOpId), expression};
    fragments.pop(4);
    fragments.push(expression_t::createNary(PROBAEXP, std::move(args), position));
}

void ExpressionBuilder::exprSimulate(int nbExpr, bool hasReach, int numberOfAcceptingRuns)
{
    // Stack:
    // conditional bound name
    // expr bound
    // nbExpr * expr
    // if (hasReach) => expr
    auto offset = nbExpr + (hasReach ? 1 : 0);
    auto& boundTypeOrBoundedExpr = fragments[2 + offset];
    auto& bound = fragments[1 + offset];
    auto runs = fragments[0 + offset];

    if (runs.getKind() == CONSTANT && runs.getType().isInteger() && runs.getValue() < 0)
        runs = makeConstant(1);

    auto args = std::vector<expression_t>{};
    args.reserve(offset + 4);  // 3-from-above + offset*expressions + numberOfAcceptingRuns
    args.push_back(runs);
    args.push_back(boundTypeOrBoundedExpr);
    args.push_back(bound);
    for (auto i = 0u; i < nbExpr; ++i)
        args.push_back(fragments[offset - 1 - i]);  // recover the original order

    if (hasReach) {
        auto& predicate = fragments[0];
        args.push_back(predicate);
        args.push_back(makeConstant(numberOfAcceptingRuns));
    }

    fragments.pop(offset + 3);
    if (hasReach)
        fragments.push(expression_t::createNary(SIMULATEREACH, std::move(args), position));
    else
        fragments.push(expression_t::createNary(SIMULATE, std::move(args), position));
}

void ExpressionBuilder::exprMitlFormula()
{
    expression_t mitl = fragments[0];
    if (!isMITL(mitl))
        mitl = toMITLAtom(mitl);
    expression_t form = expression_t::createUnary(MITLFORMULA, mitl, position);
    fragments.pop();
    fragments.push(form);
}

void ExpressionBuilder::exprMitlUntil(int low, int high)
{
    expression_t left = fragments[1];
    expression_t right = fragments[0];
    if (!isMITL(left))
        left = toMITLAtom(left);
    if (!isMITL(right))
        right = toMITLAtom(right);
    auto lowd = makeConstant(low);
    auto highd = makeConstant(high);
    auto args = std::vector<expression_t>{left, lowd, highd, right};
    expression_t form = expression_t::createNary(MITLUNTIL, std::move(args), position);
    fragments.pop(2);
    fragments.push(form);
}

void ExpressionBuilder::exprMitlRelease(int low, int high)
{
    expression_t left = fragments[1];
    expression_t right = fragments[0];
    if (!isMITL(left))
        left = toMITLAtom(left);
    if (!isMITL(right))
        right = toMITLAtom(right);
    auto lowd = makeConstant(low);
    auto highd = makeConstant(high);
    auto args = std::vector<expression_t>{left, lowd, highd, right};
    fragments.pop(2);
    fragments.push(expression_t::createNary(MITLRELEASE, std::move(args), position));
}

/*transform the diamond <>[low,high]phi into a (true U[low,high] phi) structure */
void ExpressionBuilder::exprMitlDiamond(int low, int high)
{
    auto left = expression_t::createUnary(MITLATOM, makeConstant(1));
    auto right = fragments[0];
    if (!isMITL(right))
        right = toMITLAtom(right);
    auto lowd = makeConstant(low);
    auto highd = makeConstant(high);
    auto args = std::vector<expression_t>{left, lowd, highd, right};
    expression_t form = expression_t::createNary(MITLUNTIL, std::move(args), position);
    fragments.pop(1);
    fragments.push(form);
}

/*transform the diamond [][low,high]phi into a (false R[low,high] phi) structure */
void ExpressionBuilder::exprMitlBox(int low, int high)
{
    auto left = expression_t::createUnary(MITLATOM, makeConstant(0));
    auto right = fragments[0];
    if (!isMITL(right))
        right = toMITLAtom(right);
    auto lowd = makeConstant(low);
    auto highd = makeConstant(high);
    auto args = std::vector<expression_t>{left, lowd, highd, right};
    expression_t form = expression_t::createNary(MITLRELEASE, std::move(args), position);
    fragments.pop(1);
    fragments.push(form);
}

void ExpressionBuilder::exprMitlDisj()
{
    auto& left = fragments[1];
    auto& right = fragments[0];
    expression_t form = expression_t::createBinary(MITLDISJ, left, right, position);
    fragments.pop(2);
    fragments.push(form);
}

void ExpressionBuilder::exprMitlConj()
{
    auto left = fragments[1];
    auto right = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(MITLCONJ, left, right, position));
}

void ExpressionBuilder::exprMitlNext()
{
    expression_t next = fragments[0];
    if (!isMITL(next))
        next = toMITLAtom(next);
    fragments.pop();
    fragments.push(expression_t::createUnary(MITLNEXT, next, position));
}

void ExpressionBuilder::exprMitlAtom()
{
    expression_t atom = fragments[0];
    if (!isMITL(atom)) {
        fragments.pop();
        fragments.push(expression_t::createUnary(MITLATOM, atom, position));
    }
}

void ExpressionBuilder::exprSpawn(int n)
{
    expression_t id = fragments[n];
    auto exprs = vector<expression_t>(n + 1);
    for (auto i = 0; i <= n; ++i)
        exprs[i] = fragments[n - i];
    fragments.pop(n + 1);
    fragments.push(expression_t::createNary(SPAWN, std::move(exprs), position, id.getType()));
}

void ExpressionBuilder::exprExit() { fragments.push(expression_t::createExit(position)); }

void ExpressionBuilder::exprNumOf()
{
    expression_t id = fragments[0];
    type_t t = type_t::createPrimitive(Constants::INT, position);
    fragments.pop();
    fragments.push(expression_t::createUnary(NUMOF, id, position, t));
}

void ExpressionBuilder::exprForAllDynamicBegin(const char* name, const char* temp)
{
    pushFrame(frame_t::createFrame(frames.top()));
    frames.top().addSymbol(name, type_t::createPrimitive(PROCESSVAR, position), position);
    template_t* templ = document.getDynamicTemplate(temp);
    if (!templ)
        throw UnknownDynamicTemplateError(temp);
    // dynamicFrames[name]=templ->frame;
    pushDynamicFrameOf(templ, name);
}

void ExpressionBuilder::exprForAllDynamicEnd(const char* name)
{
    // At this instant we should have expression on top of the stack and the template identifier
    // below it
    expression_t expr = fragments[0];
    expression_t process = fragments[1];
    expression_t identifier = expression_t::createIdentifier(frames.top()[0], position);
    bool mitl = isMITL(expr);
    if (mitl) {
        if (expr.getKind() == MITLATOM) {
            expr = expr.get(0).clone();
            mitl = false;
        }
    }

    auto exprs = vector<expression_t>{identifier, process, expr};
    fragments.pop(2);
    fragments.push(expression_t::createNary((mitl ? MITLFORALL : FORALLDYNAMIC), std::move(exprs), position,
                                            type_t::createPrimitive(Constants::BOOL, position)));
    popFrame();
    popDynamicFrameOf(name);
}
void ExpressionBuilder::exprExistsDynamicBegin(const char* name, const char* temp)
{
    pushFrame(frame_t::createFrame(frames.top()));
    frames.top().addSymbol(name, type_t::createPrimitive(Constants::PROCESSVAR, position), position);
    template_t* templ = document.getDynamicTemplate(temp);
    if (!templ) {
        throw UnknownDynamicTemplateError(temp);
    }
    // dynamicFrames [name]=templ->frame;
    pushDynamicFrameOf(templ, name);
}

void ExpressionBuilder::exprExistsDynamicEnd(const char* name)
{
    expression_t expr = fragments[0];
    expression_t process = fragments[1];
    expression_t identifier = expression_t::createIdentifier(frames.top()[0], position);
    bool mitl = isMITL(expr);
    if (mitl) {
        if (expr.getKind() == MITLATOM) {
            expr = expr.get(0).clone();
            mitl = false;
        }
    }
    auto exprs = vector<expression_t>{identifier, process, expr};
    fragments.pop(2);
    fragments.push(expression_t::createNary((mitl ? MITLEXISTS : EXISTSDYNAMIC), std::move(exprs), position,
                                            type_t::createPrimitive(Constants::BOOL, position)));
    popFrame();
    popDynamicFrameOf(name);
}

void ExpressionBuilder::exprSumDynamicBegin(const char* name, const char* temp)
{
    pushFrame(frame_t::createFrame(frames.top()));
    frames.top().addSymbol(name, type_t::createPrimitive(Constants::PROCESSVAR, position), position);
    template_t* templ = document.getDynamicTemplate(temp);
    if (!templ) {
        throw UnknownDynamicTemplateError(temp);
    }
    // dynamicFrames [name]=templ->frame;
    pushDynamicFrameOf(templ, name);
}

void ExpressionBuilder::exprSumDynamicEnd(const char* name)
{
    expression_t& expr = fragments[0];
    expression_t& process = fragments[1];
    expression_t identifier = expression_t::createIdentifier(frames.top()[0], position);
    auto exprs = vector<expression_t>{identifier, process, expr};
    fragments.pop(2);
    fragments.push(expression_t::createNary(SUMDYNAMIC, std::move(exprs), position, expr.getType()));
    popFrame();
    popDynamicFrameOf(name);
}

void ExpressionBuilder::exprForeachDynamicBegin(const char* name, const char* temp)
{
    pushFrame(frame_t::createFrame(frames.top()));
    frames.top().addSymbol(name, type_t::createPrimitive(Constants::PROCESSVAR, position), position);
    if (!document.getDynamicTemplate(temp)) {
        throw UnknownDynamicTemplateError(temp);
    }
    // dynamicFrames [name]=document->getDynamicTemplate(temp)->frame;
    pushDynamicFrameOf(document.getDynamicTemplate(temp), name);
}

void ExpressionBuilder::exprForeachDynamicEnd(const char* name)
{
    expression_t& expr = fragments[0];
    expression_t& process = fragments[1];
    expression_t identifier = expression_t::createIdentifier(frames.top()[0], position);
    auto exprs = vector<expression_t>{identifier, process, expr};
    fragments.pop(2);
    fragments.push(expression_t::createNary(FOREACHDYNAMIC, std::move(exprs), position,
                                            type_t::createPrimitive(Constants::INT, position)));
    popFrame();
    popDynamicFrameOf(name);
}

void ExpressionBuilder::pushDynamicFrameOf(template_t* t, string name)
{
    if (!t->isDefined) {
        throw TypeException("Template referenced before used");
    }
    dynamicFrames[name] = t->frame;
}

void ExpressionBuilder::popDynamicFrameOf(string name) { dynamicFrames.erase(name); }
