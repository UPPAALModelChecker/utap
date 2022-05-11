// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.

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

#include "utap/StatementBuilder.hpp"

#include <filesystem>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <cinttypes>
#include <cstring>

#ifdef __MINGW32__
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::string;

StatementBuilder::StatementBuilder(Document& system, std::vector<std::filesystem::path> libpaths):
    ExpressionBuilder{system}, libpaths{std::move(libpaths)}
{
    this->libpaths.emplace_back("");
}

StatementBuilder::~StatementBuilder() noexcept
{
    for (auto* b : blocks)
        delete b;
}

void StatementBuilder::collectDependencies(std::set<symbol_t>& dependencies, expression_t expr)
{
    std::set<symbol_t> symbols;
    expr.collectPossibleReads(symbols);
    while (!symbols.empty()) {
        symbol_t s = *symbols.begin();
        symbols.erase(s);
        if (dependencies.find(s) == dependencies.end()) {
            dependencies.insert(s);
            if (auto d = s.getData(); d) {
                if (auto t = s.getType(); !(t.isFunction() || t.isExternalFunction())) {
                    // assume is its variable, which is not always true
                    variable_t* v = static_cast<variable_t*>(d);
                    v->expr.collectPossibleReads(symbols);
                } else {
                    // TODO; fixme.
                }
            }
        }
    }
}

void StatementBuilder::collectDependencies(std::set<symbol_t>& dependencies, type_t type)
{
    if (type.getKind() == RANGE) {
        auto [lower, upper] = type.getRange();
        collectDependencies(dependencies, lower);
        collectDependencies(dependencies, upper);
        collectDependencies(dependencies, type[0]);
    } else {
        for (size_t i = 0; i < type.size(); i++) {
            collectDependencies(dependencies, type[i]);
        }
    }
}

void StatementBuilder::typeArrayOfSize(size_t n)
{
    /* Pop array size of fragments stack.
     */
    expression_t expr = fragments[0];
    fragments.pop();

    /* Create type.
     */
    exprNat(0);
    fragments.push(expr);
    exprNat(1);
    exprBinary(MINUS);
    typeBoundedInt(PREFIX_NONE);
    typeArrayOfType(n + 1);
}

void StatementBuilder::typeArrayOfType(size_t n)
{
    type_t size = typeFragments[0];
    typeFragments.pop();
    typeFragments[n - 1] = type_t::createArray(typeFragments[n - 1], size, position);

    /* If template local declaration, then mark all symbols in 'size'
     * and those that they depend on as restricted. Otherwise we would
     * not be able to compute the offset of a process in a set of
     * processes.
     */
    if (currentTemplate) {
        collectDependencies(currentTemplate->restricted, size);
    }

    if ((!size.isInteger() && !size.isScalar()) || !size.is(RANGE)) {
        handleError(TypeException{"$Array_must_be_defined_over_an_integer_range_or_a_scalar_set"});
    }
}

/**
 * Used to construct a new struct type, which is then pushed onto the
 * type stack. The type is based on n fields, which are expected to be
 * on and will be popped off the type stack.
 */
void StatementBuilder::typeStruct(PREFIX prefix, uint32_t n)
{
    vector<type_t> f(fields.end() - n, fields.end());
    vector<string> l(labels.end() - n, labels.end());

    fields.erase(fields.end() - n, fields.end());
    labels.erase(labels.end() - n, labels.end());

    typeFragments.push(applyPrefix(prefix, type_t::createRecord(f, l, position)));
}

/**
 * Used to declare the fields of a structure. The type of the field is
 * expected to be on the type fragment stack.
 */
void StatementBuilder::structField(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    // Constant fields are not allowed
    if (type.is(CONSTANT)) {
        handleError(TypeException{"$Constant_fields_not_allowed_in_struct"});
    }

    fields.push_back(type);
    labels.push_back(name);

    /* Check the base type. We should check this in the type
     * checker. The problem is that we do not maintain the position of
     * types, hence we cannot place the error message if we wait until
     * the type check phase.
     */
    type_t base = type.stripArray();
    if (!base.isRecord() && !base.isScalar() && !base.isIntegral()) {
        handleError(TypeException{"$Invalid_type_in_structure"});
    }
}

/**
 * A type definition. Assign the name to the given type on the type
 * fragment stack. In case of array types, dim constant expressions
 * are expected on and popped from the expression stack.
 */
void StatementBuilder::declTypeDef(const char* name)
{
    bool duplicate = frames.top().getIndexOf(name) != -1;
    type_t type = type_t::createTypeDef(name, typeFragments[0], position);
    typeFragments.pop();
    if (duplicate) {
        throw DuplicateDefinitionError(name);
    }

    frames.top().addSymbol(name, type, position);
}

static bool initRec(type_t type, int thisTypeOnly)
{
    type = type.strip();
    switch (type.getKind()) {
    case RECORD:
        for (size_t i = 0; i < type.size(); i++) {
            if (!initRec(type[i], thisTypeOnly)) {
                return false;
            }
        }
        return true;

    case ARRAY:
        if (type.getArraySize().isScalar()) {
            return false;
        }
        return initRec(type.getSub(), thisTypeOnly);
    case STRING: return true;
    default: return thisTypeOnly == 0 ? type.isIntegral() : (thisTypeOnly == 1 ? type.isClock() : type.isDouble());
    }
}

static bool initialisable(type_t type) { return initRec(type, 0) || initRec(type, 1) || initRec(type, 2); }

static bool mustInitialise(type_t type)
{
    assert(type.getKind() != FUNCTION);
    assert(type.getKind() != EXTERNAL_FUNCTION);
    assert(type.getKind() != PROCESS);
    assert(type.getKind() != INSTANCE);
    assert(type.getKind() != LSCINSTANCE);

    switch (type.getKind()) {
    case CONSTANT: return true;
    case RECORD:
        for (size_t i = 0; i < type.size(); i++) {
            if (mustInitialise(type[i])) {
                return true;
            }
        }
        return false;
    default: return type.size() > 0 && mustInitialise(type[0]);
    }
}

/**
 * Declare a new variable of the given name. The type is expected to
 * be on the type stack. If the variable has an initialiser (the init
 * parameter is true), then a constant expression is expected at the
 * top of the expression stack.  The expressions will be popped of the
 * stack (the type is left untouched).
 */
void StatementBuilder::declVar(const char* name, bool hasInit)
{
    // Pop initial value
    expression_t init;
    if (hasInit) {
        init = fragments[0];
        fragments.pop();
    }

    // Construct type
    type_t type = typeFragments[0];
    typeFragments.pop();

    // Check whether initialiser is allowed/required
    if (hasInit && !initialisable(type)) {
        handleError(TypeException{"$Cannot_have_initialiser"});
    }

    if (!hasInit && mustInitialise(type)) {
        handleError(TypeException{"$Constants_must_have_an_initialiser"});
    }

    if (currentFun && !initialisable(type)) {
        handleError(TypeException{"$Type_is_not_allowed_in_functions"});
    }

    // Add variable to document
    addVariable(type, name, init, position_t());
}

// Array and struct initialisers are represented as expressions having
// one or more values (i.e. if the stack machine program that the
// expression represent is evaluated, then one or more values will be
// left on the stack).
//
// An array or struct initialiser has the structure of a list of field
// initialisers. Each field initialiser is a named expression
// (although the name can be NULL, in which case the field is
// anonymous). The field is actually represented like any other
// expression on the expression stack, except that is has a singular
// record type (i.e. a record type with only one element) on the form
// (name,type), where name is the name of the field and type is the
// type of the expression. A list of field initialisers is then
// created by concatenating several singular recorcd types into one
// record.
//
// Example: The initialiser { 2, x: 3, 4 } is represented as an
// expression evaluating to [2,3,4] on the stack, and the type of
// expression is [(NULL, typeof(2)) x ("x", typeof(3)) x (NULL,
// typeof(4))].
//
// For struct's, care must be taken when the type of the initialiser
// is compared to that of the declared struct. If another constant
// struct is used as an initialiser, then this struct must have the
// same type name as the struct being declared. If a struct
// initialiser is used (i.e. a list of fields), then the type
// requirements are much less strict.

void StatementBuilder::declFieldInit(const char* name)
{
    type_t type = fragments[0].getType().createLabel(name, position);
    fragments[0].setType(type);
}

void StatementBuilder::declInitialiserList(uint32_t num)
{
    // Pop fields
    vector<expression_t> fields(num);
    for (uint32_t i = 0; i < num; i++) {
        fields[i] = fragments[num - 1 - i];
    }
    fragments.pop(num);

    // Compute new type (each field has a label type, see declFieldInit())
    vector<type_t> types;
    vector<string> labels;
    for (uint32_t i = 0; i < num; i++) {
        type_t type = fields[i].getType();
        types.push_back(type[0]);
        labels.push_back(type.getLabel(0));
        fields[i].setType(type[0]);
    }

    // Create list expression
    fragments.push(expression_t::createNary(LIST, fields, position, type_t::createRecord(types, labels, position)));
}

/********************************************************************
 * Function declarations
 */
void StatementBuilder::declParameter(const char* name, bool ref)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (ref) {
        type = type.createPrefix(REF);
    }

    params.addSymbol(name, type, position);
}

void StatementBuilder::declFuncBegin(const char* name)
{
    // assert(currentFun == nullptr); // the parser should recover cleanly, but it does not
    if (currentFun != nullptr) {
        /* If currentFun != nullptr, we are in an error state. This error
         * state arises when a parsing error happens in the middle of a
         * function definition, such that we do not end up calling
         * `declFuncEnd` after a `declFuncBegin`, and we have not exited
         * the scope of the function properly. Here, we just clean up the
         * scope dirtily so that we can continue parsing.
         * https://github.com/UPPAALModelChecker/uppaal/issues/402
         */
        currentFun = nullptr;
        while (!blocks.empty()) {
            delete blocks.back();
            blocks.pop_back();
        }
    }

    type_t return_type = typeFragments[0];
    typeFragments.pop();

    vector<type_t> types;
    vector<string> labels;
    for (size_t i = 0; i < params.getSize(); i++) {
        types.push_back(params[i].getType());
        labels.push_back(params[i].getName());
    }
    type_t type = type_t::createFunction(return_type, types, labels, position);
    if (!addFunction(type, name, position_t())) {
        handleError(DuplicateDefinitionError(name));
    }

    /* We maintain a stack of frames. As the function has a local
     * scope, we push a new frame and move the parameters to it.
     */
    pushFrame(frame_t::createFrame(frames.top()));
    params.moveTo(frames.top());  // params is emptied here

    /* Create function block.
     */
    currentFun->body = std::make_unique<BlockStatement>(frames.top());
    blocks.push_back(currentFun->body.get());
}

void StatementBuilder::declFuncEnd()
{
    assert(!blocks.empty());
    assert(currentFun);

    /* Recover from unterminated blocks - delete any excess blocks.
     */
    while (blocks.size() > 1) {
        delete blocks.back();
        blocks.pop_back();
    }

    assert(currentFun->body.get() == blocks.back());

    /* If function has a non void return type, then check that last
     * statement is a return statement.
     */
    if (!currentFun->uid.getType()[0].isVoid() && !currentFun->body->returns()) {
        handleError(TypeException{"$Return_statement_expected"});
    }

    /* Pop outer function block.
     */
    blocks.pop_back();

    /* Restore global frame.
     */
    popFrame();

    /* Reset current function pointer to NULL.
     */
    currentFun = nullptr;
}

void StatementBuilder::dynamicLoadLib(const char* lib)
{
    // check that we have a library
    size_t len = strlen(lib);
    if (len <= 2) {
        handleError(TypeException{"Cannot_load_empty_library_path"});
        return;
    }

    std::string name(lib + 1);
    name.erase(name.length() - 1);

    void* loaded = nullptr;
    // append ending if we are loading local file only.
#ifdef __MINGW32__
    auto path = std::filesystem::path(name + ".dll");
#elif defined(__linux__) || defined(__APPLE__)
    auto path = std::filesystem::path(name + ".so");
#else
    auto path = std::filesystem::path(name + ".so");
#endif
    if (std::filesystem::exists(path)) {
#ifdef __MINGW32__
        loaded = LoadLibrary(path.string().c_str());
#elif defined(__linux__)
        loaded = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
#elif defined(__APPLE__)
        loaded = dlopen(path.string().c_str(), RTLD_NOW | RTLD_LOCAL);
#endif
    } else {
        for (const auto& prefix : libpaths) {
            std::filesystem::path fullpath = prefix / name;
            for (size_t i = 0; i < 2; ++i) {
#ifdef __MINGW32__
                if (i == 1)
                    fullpath.concat(".dll");
                loaded = LoadLibrary(fullpath.string().c_str());  // c_str() alone uses wchar_t(!)
#elif defined(__linux__)
                if (i == 1)
                    fullpath.concat(".so");
                loaded = dlopen(fullpath.c_str(), RTLD_NOW | RTLD_LOCAL);
#elif defined(__APPLE__)
                if (i == 1)
                    fullpath.append(".so");
                loaded = dlopen(fullpath.c_str(), RTLD_NOW | RTLD_LOCAL);
#endif
                if (loaded != nullptr)
                    break;
            }
            if (loaded != nullptr)
                break;
        }
    }
    if (loaded == nullptr) {
        handleError(CouldNotLoadLibraryError(name));
    }
    document.addLibrary(loaded);
}

void StatementBuilder::declExternalFunc(const char* name, const char* alias)
{
    assert(currentFun == nullptr);

    type_t return_type = typeFragments[0];
    typeFragments.pop();

    vector<type_t> types;
    vector<string> labels;
    for (size_t i = 0; i < params.getSize(); i++) {
        types.push_back(params[i].getType());
        labels.push_back(params[i].getName());
    }

    void* fp = nullptr;
#ifdef __MINGW32__
    fp = (void*)GetProcAddress((HMODULE)document.lastLibrary(), name);
#elif __linux__
    fp = dlsym(document.lastLibrary(), name);
#endif

    if (fp == nullptr) {
        handleError(CouldNotLoadFunctionError(name));
    }

    type_t type = type_t::createExternalFunction(return_type, types, labels, position);
    if (!addFunction(type, alias, position_t())) {
        handleError(DuplicateDefinitionError(alias));
    }
    pushFrame(frame_t::createFrame(frames.top()));
    params.moveTo(frames.top());  // params is emptied here
    currentFun->body = std::make_unique<ExternalBlockStatement>(frames.top(), fp, !return_type.isVoid());
    blocks.push_back(currentFun->body.get());
    declFuncEnd();
}

/*********************************************************************
 * Statements
 */
void StatementBuilder::blockBegin()
{
    pushFrame(frame_t::createFrame(frames.top()));
    blocks.push_back(new BlockStatement(frames.top()));
}

void StatementBuilder::blockEnd()
{
    // Append the block which is being terminated as a statement to
    // the containing block.
    BlockStatement* block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(std::unique_ptr<BlockStatement>(block));

    // Restore containing frame
    popFrame();
}

void StatementBuilder::emptyStatement() { blocks.back()->push_stat(std::make_unique<EmptyStatement>()); }

void StatementBuilder::forBegin() {}

void StatementBuilder::forEnd()
{  // 3 expr, 1 stat
    auto substat = blocks.back()->pop_stat();
    auto forstat = std::make_unique<ForStatement>(fragments[2], fragments[1], fragments[0], std::move(substat));
    blocks.back()->push_stat(std::move(forstat));

    fragments.pop(3);
}

void StatementBuilder::iterationBegin(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    /* The iterator cannot be modified.
     */
    if (!type.is(CONSTANT)) {
        type = type.createPrefix(CONSTANT);
    }

    /* The iteration statement has a local scope for the iterator.
     */
    pushFrame(frame_t::createFrame(frames.top()));

    /* Add variable.
     */
    variable_t* variable = addVariable(type, name, expression_t(), position_t());

    /* Create a new statement for the loop. We need to already create
     * this here as the statement is the only thing that can keep the
     * reference to the frame.
     */
    blocks.back()->push_stat(std::make_unique<IterationStatement>(variable->uid, frames.top(), nullptr));
}

void StatementBuilder::iterationEnd(const char* name)
{
    /* Retrieve the statement that we iterate over.
     */
    auto statement = blocks.back()->pop_stat();

    if (!blocks.back()->empty()) {
        // If the syntax is wrong, we won't have anything in blocks.back()
        /* Add statement to loop construction.  */
        static_cast<IterationStatement*>(blocks.back()->back())->stat = std::move(statement);
    }

    /* Restore the frame pointer.
     */
    popFrame();
}

void StatementBuilder::whileBegin() {}

void StatementBuilder::whileEnd()
{  // 1 expr, 1 stat
    auto whilestat = std::make_unique<WhileStatement>(fragments[0], blocks.back()->pop_stat());
    blocks.back()->push_stat(std::move(whilestat));
    fragments.pop();
}

void StatementBuilder::doWhileBegin() {}

void StatementBuilder::doWhileEnd()
{  // 1 stat, 1 expr
    auto substat = blocks.back()->pop_stat();
    blocks.back()->push_stat(std::make_unique<DoWhileStatement>(std::move(substat), fragments[0]));
    fragments.pop();
}

void StatementBuilder::ifEnd(bool elsePart)
{  // 1 expr, 1 or 2 statements
    std::unique_ptr<Statement> falseCase;
    if (elsePart)
        falseCase = blocks.back()->pop_stat();
    auto trueCase = blocks.back()->pop_stat();
    auto ifstat = std::make_unique<IfStatement>(fragments[0], std::move(trueCase), std::move(falseCase));
    blocks.back()->push_stat(std::move(ifstat));
    fragments.pop();
}

void StatementBuilder::exprStatement()
{  // 1 expr
    blocks.back()->push_stat(std::make_unique<ExprStatement>(fragments[0]));
    fragments.pop();
}

void StatementBuilder::returnStatement(bool args)
{  // 1 expr if argument is true
    if (!currentFun) {
        handleError(TypeException{"$Cannot_return_outside_of_function_declaration"});
    } else {
        /* Only functions with non-void return type are allowed to have
         * arguments on return.
         */
        type_t return_type = currentFun->uid.getType()[0];
        if (return_type.isVoid() && args) {
            handleError(TypeException{"$return_with_a_value_in_function_returning_void"});
        } else if (!return_type.isVoid() && !args) {
            handleError(TypeException{"$return_with_no_value_in_function_returning_non-void"});
        }

        std::unique_ptr<ReturnStatement> stat;
        if (args) {
            stat = std::make_unique<ReturnStatement>(fragments[0]);
            fragments.pop();
        } else {
            stat = std::make_unique<ReturnStatement>();
        }
        blocks.back()->push_stat(std::move(stat));
    }
}

void StatementBuilder::assertStatement()
{
    blocks.back()->push_stat(std::make_unique<AssertStatement>(fragments[0]));
    fragments.pop();
}

/********************************************************************
 * Expressions
 */

void StatementBuilder::exprCallBegin()
{
    ExpressionBuilder::exprCallBegin();

    /* Check for recursive function calls. We could move this to
     * the type checker.
     */
    if (currentFun != nullptr && currentFun->uid == fragments[0].getSymbol()) {
        handleError(TypeException{"$Recursion_is_not_allowed"});
    }
}
