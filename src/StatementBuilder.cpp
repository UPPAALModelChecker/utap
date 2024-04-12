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

StatementBuilder::StatementBuilder(Document& doc, std::vector<std::filesystem::path> libpaths):
    ExpressionBuilder{doc}, libpaths{std::move(libpaths)}
{
    this->libpaths.insert(this->libpaths.begin(), std::filesystem::current_path());
    this->libpaths.insert(this->libpaths.begin(), "");
}

void StatementBuilder::collectDependencies(std::set<symbol_t>& dependencies, expression_t expr)
{
    std::set<symbol_t> symbols;
    expr.collect_possible_reads(symbols);
    while (!symbols.empty()) {
        symbol_t s = *symbols.begin();
        symbols.erase(s);
        if (dependencies.find(s) == dependencies.end()) {
            dependencies.insert(s);
            if (auto d = s.get_data(); d) {
                if (auto t = s.get_type(); !(t.is_function() || t.is_function_external())) {
                    // assume is its variable, which is not always true
                    variable_t* v = static_cast<variable_t*>(d);
                    v->init.collect_possible_reads(symbols);
                } else {
                    // TODO; fixme.
                }
            }
        }
    }
}

void StatementBuilder::collectDependencies(std::set<symbol_t>& dependencies, type_t type)
{
    if (type.get_kind() == RANGE) {
        auto [lower, upper] = type.get_range();
        collectDependencies(dependencies, lower);
        collectDependencies(dependencies, upper);
        collectDependencies(dependencies, type[0]);
    } else {
        for (size_t i = 0; i < type.size(); i++) {
            collectDependencies(dependencies, type[i]);
        }
    }
}

void StatementBuilder::type_array_of_size(size_t n)
{
    /* Pop array size of fragments stack.
     */
    expression_t expr = fragments[0];
    fragments.pop();

    /* Create type.
     */
    expr_nat(0);
    fragments.push(expr);
    expr_nat(1);
    expr_binary(MINUS);
    type_bounded_int(PREFIX_NONE);
    type_array_of_type(n + 1);
}

void StatementBuilder::type_array_of_type(size_t n)
{
    type_t size = typeFragments[0];
    typeFragments.pop();
    typeFragments[n - 1] = type_t::create_array(typeFragments[n - 1], size, position);

    /* If template local declaration, then mark all symbols in 'size'
     * and those that they depend on as restricted. Otherwise we would
     * not be able to compute the offset of a process in a set of
     * processes.
     */
    if (currentTemplate) {
        collectDependencies(currentTemplate->restricted, size);
    }

    if ((!size.is_integer() && !size.is_scalar()) || !size.is(RANGE)) {
        handle_error(TypeException{"$Array_must_be_defined_over_an_integer_range_or_a_scalar_set"});
    }
}

/**
 * Used to construct a new struct type, which is then pushed onto the
 * type stack. The type is based on n fields, which are expected to be
 * on and will be popped off the type stack.
 */
void StatementBuilder::type_struct(PREFIX prefix, uint32_t n)
{
    auto f = vector<type_t>(fields.end() - n, fields.end());
    auto l = vector<string>(labels.end() - n, labels.end());
    auto p = vector<position_t>(positions.end() - n, positions.end());

    fields.erase(fields.end() - n, fields.end());
    labels.erase(labels.end() - n, labels.end());
    positions.erase(positions.end() - n, positions.end());

    typeFragments.push(apply_prefix(prefix, type_t::create_record(f, l, p, position)));
}

/**
 * Used to declare the fields of a structure. The type of the field is
 * expected to be on the type fragment stack.
 */
void StatementBuilder::struct_field(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    // Constant fields are not allowed
    if (type.is(CONSTANT)) {
        handle_error(TypeException{"$Constant_fields_not_allowed_in_struct"});
    }

    fields.push_back(type);
    labels.push_back(name);
    positions.push_back(position);

    /* Check the base type. We should check this in the type
     * checker. The problem is that we do not maintain the position of
     * types, hence we cannot place the error message if we wait until
     * the type check phase.
     */
    type_t base = type.strip_array();
    if (!base.is_record() && !base.is_scalar() && !base.is_integral()) {
        handle_error(TypeException{"$Invalid_type_in_structure"});
    }
}

/**
 * A type definition. Assign the name to the given type on the type
 * fragment stack. In case of array types, dim constant expressions
 * are expected on and popped from the expression stack.
 */
void StatementBuilder::decl_typedef(const char* name)
{
    bool duplicate = frames.top().contains(name);
    type_t type = type_t::create_typedef(name, typeFragments[0], position);
    typeFragments.pop();
    if (duplicate) {
        throw DuplicateDefinitionError(name);
    }

    frames.top().add_symbol(name, type, position);
}

static bool initRec(type_t type, int thisTypeOnly)
{
    type = type.strip();
    switch (type.get_kind()) {
    case RECORD:
        for (size_t i = 0; i < type.size(); i++) {
            if (!initRec(type[i], thisTypeOnly)) {
                return false;
            }
        }
        return true;

    case ARRAY:
        if (type.get_array_size().is_scalar()) {
            return false;
        }
        return initRec(type.get_sub(), thisTypeOnly);
    case STRING: return true;
    default: return thisTypeOnly == 0 ? type.is_integral() : (thisTypeOnly == 1 ? type.is_clock() : type.is_double());
    }
}

static bool initialisable(type_t type) { return initRec(type, 0) || initRec(type, 1) || initRec(type, 2); }

static bool mustInitialise(type_t type)
{
    const auto k = type.get_kind();
    assert(k != FUNCTION);
    assert(k != FUNCTION_EXTERNAL);
    assert(k != PROCESS);
    assert(k != INSTANCE);
    assert(k != LSC_INSTANCE);

    switch (k) {
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
void StatementBuilder::decl_var(const char* name, bool hasInit)
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
        handle_error(TypeException{"$Cannot_have_initialiser"});
    }

    if (!hasInit && mustInitialise(type)) {
        handle_error(TypeException{"$Constants_must_have_an_initialiser"});
    }

    if (currentFun && !initialisable(type)) {
        handle_error(TypeException{"$Type_is_not_allowed_in_functions"});
    }

    // Add variable to document
    addVariable(type, name, init, position);
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

void StatementBuilder::decl_field_init(const char* name)
{
    type_t type = fragments[0].get_type().create_label(name, position);
    fragments[0].set_type(type);
}

void StatementBuilder::decl_init_list(uint32_t num)
{
    // Pop fields
    vector<expression_t> fields(num);
    for (uint32_t i = 0; i < num; i++) {
        fields[i] = fragments[num - 1 - i];
    }
    fragments.pop(num);

    // Compute new type (each field has a label type, see decl_field_init())
    vector<type_t> types;
    vector<string> labels;
    vector<position_t> positions;
    for (uint32_t i = 0; i < num; i++) {
        type_t type = fields[i].get_type();
        types.push_back(type[0]);
        labels.push_back(type.get_label(0));
        fields[i].set_type(type[0]);
        positions.push_back(fields[i].get_position());
    }

    // Create list expression
    fragments.push(
        expression_t::create_nary(LIST, fields, position, type_t::create_record(types, labels, positions, position)));
}

/********************************************************************
 * Function declarations
 */
void StatementBuilder::decl_parameter(const char* name, bool ref)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (ref) {
        type = type.create_prefix(REF);
    }

    params.add_symbol(name, type, position);
}

void StatementBuilder::func_type()
{
    if (currentFun != nullptr) {
        /* If currentFun != nullptr, we are in an error state. This error
         * state arises when a parsing error happens in the middle of a
         * function definition, such that we do not end up calling
         * `decl_func_end` after a `decl_func_begin`, and we have not exited
         * the scope of the function properly. Here, we just clean up the
         * scope dirtily so that we can continue parsing.
         * https://github.com/UPPAALModelChecker/uppaal/issues/402
         */
        currentFun = nullptr;
        blocks.clear();
    }

    type_t return_type = typeFragments[0];

    vector<type_t> types;
    vector<string> labels;
    for (size_t i = 0; i < params.get_size(); i++) {
        types.push_back(params[i].get_type());
        labels.push_back(params[i].get_name());
    }

    typeFragments[0] = type_t::create_function(return_type, types, labels, position);
}

void StatementBuilder::decl_func_begin(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (!addFunction(type, name, position)) {
        handle_error(DuplicateDefinitionError(name));
    }

    /* We maintain a stack of frames. As the function has a local
     * scope, we push a new frame and move the parameters to it.
     */
    push_frame(frame_t::create(frames.top()));
    params.move_to(frames.top());  // params is emptied here

    /* Create function block.
     */
    currentFun->body = std::make_unique<BlockStatement>(frames.top());
}

BlockStatement& StatementBuilder::get_block() { return blocks.empty() ? *currentFun->body : *blocks.back(); }

void StatementBuilder::decl_func_end()
{
    assert(currentFun);
    assert(currentFun->body);

    /* Recover from unterminated blocks - delete any excess blocks.
     */
    blocks.clear();

    /* If function has a non void return type, then check that last
     * statement is a return statement.
     */
    if (!currentFun->uid.get_type()[0].is_void() && !currentFun->body->returns()) {
        handle_error(TypeException{"$Return_statement_expected"});
    }

    currentFun->body_position = position;

    /* Restore global frame.
     */
    popFrame();

    /* Reset current function pointer to NULL.
     */
    currentFun = nullptr;
}

void StatementBuilder::dynamic_load_lib(const char* lib)
{
    // check that we have a library
    size_t len = strlen(lib);
    if (len <= 2) {
        handle_error(TypeException{"Cannot_load_empty_library_path"});
        return;
    }
    auto name = std::string(lib + 1, len - 2);  // strip the quote marks
    auto errors = std::vector<std::string>{};   // buffer the errors
    auto success = false;
    for (const auto& dir : libpaths) {
        auto path = dir / name;
        try {
            document.add(library_t{path.string().c_str()});
            success = true;
            break;
        } catch (const std::runtime_error& ex) {
            errors.push_back(ex.what());
            continue;
        }
    }
    if (!success) {  // reveal errors iff loading has failed
        for (auto& e : errors)
            handle_error(TypeException{e});
    }
}

void StatementBuilder::decl_external_func(const char* name, const char* alias)
{
    assert(currentFun == nullptr);

    type_t return_type = typeFragments[0];
    typeFragments.pop();

    vector<type_t> types;
    vector<string> labels;
    for (size_t i = 0; i < params.get_size(); i++) {
        types.push_back(params[i].get_type());
        labels.push_back(params[i].get_name());
    }

    void* fp = nullptr;
    try {
        fp = document.last_library().get_symbol(name);
    } catch (const std::runtime_error& ex) {
        handle_error(TypeException{ex.what()});
    }

    type_t type = type_t::create_external_function(return_type, types, labels, position);
    if (!addFunction(type, alias, position_t())) {
        handle_error(DuplicateDefinitionError(alias));
    }
    push_frame(frame_t::create(frames.top()));
    params.move_to(frames.top());  // params is emptied here
    currentFun->body = std::make_unique<ExternalBlockStatement>(frames.top(), fp, !return_type.is_void());
    decl_func_end();
}

/*********************************************************************
 * Statements
 */
void StatementBuilder::block_begin()
{
    push_frame(frame_t::create(frames.top()));
    blocks.push_back(std::make_unique<BlockStatement>(frames.top()));
}

void StatementBuilder::block_end()
{
    // Append the block which is being terminated as a statement to
    // the containing block.
    std::unique_ptr<BlockStatement> block = std::move(blocks.back());
    blocks.pop_back();
    get_block().push_stat(std::move(block));

    // Restore containing frame
    popFrame();
}

void StatementBuilder::empty_statement() { get_block().push_stat(std::make_unique<EmptyStatement>()); }

void StatementBuilder::for_begin() {}

void StatementBuilder::for_end()
{  // 3 expr, 1 stat
    auto substat = get_block().pop_stat();
    auto forstat = std::make_unique<ForStatement>(fragments[2], fragments[1], fragments[0], std::move(substat));
    get_block().push_stat(std::move(forstat));

    fragments.pop(3);
}

void StatementBuilder::iteration_begin(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    /* The iterator cannot be modified.
     */
    if (!type.is(CONSTANT)) {
        type = type.create_prefix(CONSTANT);
    }

    /* The iteration statement has a local scope for the iterator.
     */
    push_frame(frame_t::create(frames.top()));

    /* Add variable.
     */
    variable_t* variable = addVariable(type, name, expression_t(), position_t());

    /* Create a new statement for the loop. We need to already create
     * this here as the statement is the only thing that can keep the
     * reference to the frame.
     */
    get_block().push_stat(std::make_unique<IterationStatement>(variable->uid, frames.top(), nullptr));
}

void StatementBuilder::iteration_end(const char* name)
{
    /* Retrieve the statement that we iterate over.
     */
    auto statement = get_block().pop_stat();

    if (!get_block().empty()) {
        // If the syntax is wrong, we won't have anything in blocks.back()
        /* Add statement to loop construction.  */
        static_cast<IterationStatement*>(get_block().back())->stat = std::move(statement);
    }

    /* Restore the frame pointer.
     */
    popFrame();
}

void StatementBuilder::while_begin() {}

void StatementBuilder::while_end()
{  // 1 expr, 1 stat
    auto whilestat = std::make_unique<WhileStatement>(fragments[0], get_block().pop_stat());
    get_block().push_stat(std::move(whilestat));
    fragments.pop();
}

void StatementBuilder::do_while_begin() {}

void StatementBuilder::do_while_end()
{  // 1 stat, 1 expr
    auto substat = get_block().pop_stat();
    get_block().push_stat(std::make_unique<DoWhileStatement>(std::move(substat), fragments[0]));
    fragments.pop();
}

void StatementBuilder::if_end(bool elsePart)
{  // 1 expr, 1 or 2 statements
    std::unique_ptr<Statement> falseCase;
    if (elsePart)
        falseCase = get_block().pop_stat();
    auto trueCase = get_block().pop_stat();
    auto ifstat = std::make_unique<IfStatement>(fragments[0], std::move(trueCase), std::move(falseCase));
    get_block().push_stat(std::move(ifstat));
    fragments.pop();
}

void StatementBuilder::expr_statement()
{  // 1 expr
    get_block().push_stat(std::make_unique<ExprStatement>(fragments[0]));
    fragments.pop();
}

void StatementBuilder::return_statement(bool args)
{  // 1 expr if argument is true
    if (!currentFun) {
        handle_error(TypeException{"$Cannot_return_outside_of_function_declaration"});
    } else {
        /* Only functions with non-void return type are allowed to have
         * arguments on return.
         */
        type_t return_type = currentFun->uid.get_type()[0];
        if (return_type.is_void() && args) {
            handle_error(TypeException{"$return_with_a_value_in_function_returning_void"});
        } else if (!return_type.is_void() && !args) {
            handle_error(TypeException{"$return_with_no_value_in_function_returning_non-void"});
        }

        std::unique_ptr<ReturnStatement> stat;
        if (args) {
            stat = std::make_unique<ReturnStatement>(fragments[0]);
            fragments.pop();
        } else {
            stat = std::make_unique<ReturnStatement>();
        }
        get_block().push_stat(std::move(stat));
    }
}

void StatementBuilder::assert_statement()
{
    get_block().push_stat(std::make_unique<AssertStatement>(fragments[0]));
    fragments.pop();
}

/********************************************************************
 * Expressions
 */

void StatementBuilder::expr_call_begin()
{
    ExpressionBuilder::expr_call_begin();

    /* Check for recursive function calls. We could move this to
     * the type checker.
     */
    if (currentFun != nullptr && currentFun->uid == fragments[0].get_symbol()) {
        handle_error(TypeException{"$Recursion_is_not_allowed"});
    }
}
