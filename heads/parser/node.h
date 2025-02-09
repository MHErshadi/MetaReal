/*
MIT License

Copyright (c) 2023 MetaReal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

/**
 * @file node.h
 * Definitions of the node data structure which is used by the parser to create AST (abstract syntax tree) of the code. \n
 * All things defined in this file have the \a mr_node prefix.
*/

#ifndef __MR_NODE__
#define __MR_NODE__

#include <defs.h>

/** 
 * @struct __MR_NODE_T
 * Sentence equivalent in the compilation process. \n
 * The node contains all the information needed about an statement and the grammar of that statement.
 * @var mr_byte_t __MR_NODE_T::type
 * Type of the <em>node</em>.
 * @var mr_long_t __MR_NODE_T::value
 * Value of the <em>node</em>.
*/
#pragma pack(push, 1)
struct __MR_NODE_T
{
    mr_long_t value;
    mr_byte_t type;
};
#pragma pack(pop)
typedef struct __MR_NODE_T mr_node_t;

/**
 * @enum __MR_NODE_ENUM
 * List of valid node types.
 * @var __MR_NODE_ENUM::MR_NODE_NULL
 * Null node type (used for missing nodes).
 * @var __MR_NODE_ENUM::MR_NODE_NONE
 * \a None node type.
 * @var __MR_NODE_ENUM::MR_NODE_INT
 * \a Integer node type.
 * @var __MR_NODE_ENUM::MR_NODE_FLOAT
 * \a Float node type.
 * @var __MR_NODE_ENUM::MR_NODE_IMAGINARY
 * \a Imaginary node type.
 * @var __MR_NODE_ENUM::MR_NODE_BOOL
 * \a Boolean node type.
 * @var __MR_NODE_ENUM::MR_NODE_CHR
 * \a Character node type.
 * @var __MR_NODE_ENUM::MR_NODE_FSTR_FRAG
 * Fragment of a formatted string (string parts).
 * @var __MR_NODE_ENUM::MR_NODE_STR
 * \a String node type.
 * @var __MR_NODE_ENUM::MR_NODE_FSTR
 * <em>Formatted String</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_LIST
 * \a List node type.
 * @var __MR_NODE_ENUM::MR_NODE_TUPLE
 * \a Tuple node type.
 * @var __MR_NODE_ENUM::MR_NODE_DICT
 * \a Dictionary node type.
 * @var __MR_NODE_ENUM::MR_NODE_SET
 * \a Set node type.
 * @var __MR_NODE_ENUM::MR_NODE_TYPE
 * \a Type node type.
 * @var __MR_NODE_ENUM::MR_NODE_BINARY_OP
 * <em>Binary operation</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_UNARY_OP
 * <em>Unary operation</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_TERNARY_OP
 * <em>Ternary operation</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_SUBSCRIPT
 * \a Subscript node type (index).
 * @var __MR_NODE_ENUM::MR_NODE_SUBSCRIPT_END
 * \a Subscript node type (start and end).
 * @var __MR_NODE_ENUM::MR_NODE_SUBSCRIPT_STEP
 * \a Subscript node type (start, end, and step).
 * @var __MR_NODE_ENUM::MR_NODE_VAR_ACCESS
 * <em>Variable access</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_VAR_ASSIGN
 * <em>Variable assignment</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_FUNC_CALL
 * <em>Function call</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_EX_FUNC_CALL
 * <em>Exclusive function call</em> node type with an empty list of parameters.
 * @var __MR_NODE_ENUM::MR_NODE_DOLLAR_METHOD
 * <em>Dollar method call</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_EX_DOLLAR_METHOD
 * <em>Exclusive dollar method call</em> node type with an empty list of parameters.
 * @var __MR_NODE_ENUM::MR_NODE_MULTILINE
 * \a Multiline node type (used for bodies of the statements).
 * @var __MR_NODE_ENUM::MR_NODE_IF
 * <em>If statement</em> node type (if).
 * @var __MR_NODE_ENUM::MR_NODE_IF_ELSE
 * <em>If statement</em> node type (if and else).
 * @var __MR_NODE_ENUM::MR_NODE_IF_ELIF
 * <em>If statement</em> node type (if, elif, and else).
 * @var __MR_NODE_ENUM::MR_NODE_SWITCH
 * <em>Switch statement</em> node type (case).
 * @var __MR_NODE_ENUM::MR_NODE_SWITCH_DEF
 * <em>Switch statement</em> node type (case and default).
 * @var __MR_NODE_ENUM::MR_NODE_IMPORT
 * <em>Import statement</em> node type.
 * @var __MR_NODE_ENUM::MR_NODE_INCLUDE
 * <em>Include statement</em> node type.
*/
enum __MR_NODE_ENUM
{
    MR_NODE_NULL,
    MR_NODE_NONE,

    MR_NODE_INT,
    MR_NODE_FLOAT,
    MR_NODE_IMAGINARY,
    MR_NODE_BOOL,
    MR_NODE_CHR,
    MR_NODE_FSTR_FRAG,

    MR_NODE_STR,
    MR_NODE_FSTR,
    MR_NODE_LIST,
    MR_NODE_TUPLE,
    MR_NODE_DICT,
    MR_NODE_SET,
    MR_NODE_TYPE,

    MR_NODE_BINARY_OP,
    MR_NODE_UNARY_OP,
    MR_NODE_TERNARY_OP,

    MR_NODE_SUBSCRIPT,
    MR_NODE_SUBSCRIPT_END,
    MR_NODE_SUBSCRIPT_STEP,

    MR_NODE_VAR_ACCESS,
    MR_NODE_VAR_ASSIGN,

    MR_NODE_FUNC_CALL,
    MR_NODE_EX_FUNC_CALL,

    MR_NODE_DOLLAR_METHOD,
    MR_NODE_EX_DOLLAR_METHOD,

    MR_NODE_MULTILINE,
    MR_NODE_MULTILINE_TUPLE,

    MR_NODE_IF,
    MR_NODE_IF_ELSE,
    MR_NODE_IF_ELIF,

    MR_NODE_SWITCH,
    MR_NODE_SWITCH_DEF,

    MR_NODE_IMPORT,
    MR_NODE_INCLUDE
};

/**
 * Number of valid nodes.
*/
#define MR_NODE_COUNT (MR_NODE_INCLUDE + 1)

/**
 * @struct __MR_NODE_KEYVAL_T
 * Data structure that holds information about a single key-value. \n
 * This structure is used by the \a __MR_NODE_LIST_T data structure (for dictionaries).
 * @var mr_node_t __MR_NODE_KEYVAL_T::key
 * Key of the key-value.
 * @var mr_node_t __MR_NODE_KEYVAL_T::value
 * Value of the key-value.
*/
#pragma pack(push, 1)
struct __MR_NODE_KEYVAL_T
{
    mr_node_t key;
    mr_node_t value;
};
#pragma pack(pop)
typedef struct __MR_NODE_KEYVAL_T mr_node_keyval_t;

/**
 * @struct __MR_NODE_LIST_T
 * Data structure that holds information about a fstr, list, dict, or a set.
 * @var mr_idx_t __MR_NODE_LIST_T::elems
 * The list of elements.
 * @var mr_idx_t __MR_NODE_LIST_T::size
 * Size of the elements list.
 * @var mr_idx_t __MR_NODE_LIST_T::sidx
 * Starting index of the list.
 * @var mr_idx_t __MR_NODE_LIST_T::eidx
 * Ending index of the list.
*/
#pragma pack(push, 1)
struct __MR_NODE_LIST_T
{
    mr_idx_t elems;
    mr_idx_t size;
    mr_idx_t sidx;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_LIST_T mr_node_list_t;

/**
 * @struct __MR_NODE_TUPLE_T
 * Data structure that holds information about a tuple.
 * @var mr_idx_t __MR_NODE_TUPLE_T::elems
 * The list of elements.
 * @var mr_idx_t __MR_NODE_TUPLE_T::size
 * Size of the elements list.
*/
#pragma pack(push, 1)
struct __MR_NODE_TUPLE_T
{
    mr_idx_t elems;
    mr_idx_t size;
};
#pragma pack(pop)
typedef struct __MR_NODE_TUPLE_T mr_node_tuple_t;

/**
 * @struct __MR_NODE_BINARY_OP_T
 * Data structure that holds information about a binary operation.
 * @var mr_node_t __MR_NODE_BINARY_OP_T::left
 * Left operand of the operation.
 * @var mr_node_t __MR_NODE_BINARY_OP_T::right
 * Right operand of the operation.
 * @var mr_byte_t __MR_NODE_BINARY_OP_T::op
 * Operator of the operation.
*/
#pragma pack(push, 1)
struct __MR_NODE_BINARY_OP_T
{
    mr_node_t left;
    mr_node_t right;
    mr_byte_t op;
};
#pragma pack(pop)
typedef struct __MR_NODE_BINARY_OP_T mr_node_binary_op_t;

/**
 * @struct __MR_NODE_UNARY_OP_T
 * Data structure that holds information about a unary operation.
 * @var mr_node_t __MR_NODE_UNARY_OP_T::operand
 * Operand of the operation.
 * @var mr_idx_t __MR_NODE_UNARY_OP_T::sidx
 * Starting index of operation.
 * @var mr_byte_t __MR_NODE_UNARY_OP_T::op
 * Operator of the operation.
*/
#pragma pack(push, 1)
struct __MR_NODE_UNARY_OP_T
{
    mr_node_t operand;
    mr_idx_t sidx;
    mr_byte_t op;
};
#pragma pack(pop)
typedef struct __MR_NODE_UNARY_OP_T mr_node_unary_op_t;

/**
 * @struct __MR_NODE_TERNARY_OP_T
 * Data structure that holds information about a ternary operation.
 * @var mr_node_t __MR_NODE_TERNARY_OP_T::cond
 * Condition of the ternary operation.
 * @var mr_node_t __MR_NODE_TERNARY_OP_T::left
 * Left operand of the ternary operation.
 * @var mr_node_t __MR_NODE_TERNARY_OP_T::right
 * Right operand of the ternary operation.
*/
#pragma pack(push, 1)
struct __MR_NODE_TERNARY_OP_T
{
    mr_node_t cond;
    mr_node_t left;
    mr_node_t right;
};
#pragma pack(pop)
typedef struct __MR_NODE_TERNARY_OP_T mr_node_ternary_op_t;

/**
 * @struct __MR_NODE_SUBSCRIPT_T
 * Data structure that holds information about a subscript operation (index).
 * @var mr_node_t __MR_NODE_SUBSCRIPT_T::node
 * Subscriptable node.
 * @var mr_node_t __MR_NODE_SUBSCRIPT_T::idx
 * Index of the subscript.
 * @var mr_idx_t __MR_NODE_SUBSCRIPT_T::eidx
 * Ending index of the operation.
*/
#pragma pack(push, 1)
struct __MR_NODE_SUBSCRIPT_T
{
    mr_node_t node;
    mr_node_t idx;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_SUBSCRIPT_T mr_node_subscript_t;

/**
 * Data structure that holds information about a subscript operation (start and end).
 * @var mr_node_t __MR_NODE_SUBSCRIPT_END_T::node
 * Subscriptable node.
 * @var mr_node_t __MR_NODE_SUBSCRIPT_END_T::start
 * Starting index of the subscript.
 * @var mr_node_t __MR_NODE_SUBSCRIPT_END_T::end
 * Ending index of the subscript.
 * @var mr_idx_t __MR_NODE_SUBSCRIPT_END_T::eidx
 * Ending index of the operation.
*/
#pragma pack(push, 1)
struct __MR_NODE_SUBSCRIPT_END_T
{
    mr_node_t node;
    mr_node_t start;
    mr_node_t end;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_SUBSCRIPT_END_T mr_node_subscript_end_t;

/**
 * @struct __MR_NODE_SUBSCRIPT_STEP_T
 * Data structure that holds information about a subscript operation (start, end, and step).
 * @var mr_node_t __MR_NODE_SUBSCRIPT_STEP_T::node
 * Subscriptable node.
 * @var mr_node_t __MR_NODE_SUBSCRIPT_STEP_T::start
 * Starting index of the subscript.
 * @var mr_node_t __MR_NODE_SUBSCRIPT_STEP_T::end
 * Ending index of the subscript.
 * @var mr_node_t __MR_NODE_SUBSCRIPT_STEP_T::step
 * Step of the subscript iterated over the <em>node</em>.
 * @var mr_idx_t __MR_NODE_SUBSCRIPT_STEP_T::eidx
 * Ending index of the operation.
*/
#pragma pack(push, 1)
struct __MR_NODE_SUBSCRIPT_STEP_T
{
    mr_node_t node;
    mr_node_t start;
    mr_node_t end;
    mr_node_t step;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_SUBSCRIPT_STEP_T mr_node_subscript_step_t;

/**
 * @struct __MR_NODE_VAR_ASSIGN_T
 * Data structure that holds information about a variable assignment.
 * @var mr_idx_t __MR_NODE_VAR_ASSIGN_T::name
 * Starting index of the name.
 * @var mr_byte_t __MR_NODE_VAR_ASSIGN_T::access
 * A two-bit value that determines which access keyword is used. \n
 * 00: no access keyword. \n
 * 01: \a private keyword. \n
 * 10: \a public keyword. \n
 * 11: \a protected keyword.
 * @var mr_bool_t __MR_NODE_VAR_ASSIGN_T::is_global
 * A boolean value that determines if the \a global keyword is used or not.
 * @var mr_bool_t __MR_NODE_VAR_ASSIGN_T::is_readonly
 * A boolean value that determines if the \a readonly keyword is used or not.
 * @var mr_bool_t __MR_NODE_VAR_ASSIGN_T::is_const
 * A boolean value that determines if the \a const keyword is used or not.
 * @var mr_bool_t __MR_NODE_VAR_ASSIGN_T::is_static
 * A boolean value that determines if the \a static keyword is used or not.
 * @var mr_bool_t __MR_NODE_VAR_ASSIGN_T::is_link
 * A boolean value that determines if the assignment is linking or not.
 * @var mr_node_t __MR_NODE_VAR_ASSIGN_T::value
 * Value of the assignment.
 * @var mr_byte_t __MR_NODE_VAR_ASSIGN_T::type
 * Type of the variable (if specified). \n
 * If the type is not specified in the code, the \a type would be equal to <em>MR_TOKEN_EOF</em>.
 * @var mr_idx_t __MR_NODE_VAR_ASSIGN_T::sidx
 * Starting index of the node.
*/
#pragma pack(push, 1)
struct __MR_NODE_VAR_ASSIGN_T
{
    mr_idx_t name;
    mr_byte_t access : 2;
    mr_bool_t is_global : 1;
    mr_bool_t is_readonly : 1;
    mr_bool_t is_const : 1;
    mr_bool_t is_static : 1;
    mr_bool_t is_link : 1;
    mr_node_t value;
    mr_byte_t type;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_VAR_ASSIGN_T mr_node_var_assign_t;

/**
 * @struct __MR_NODE_CALL_ARG_T
 * Data structure that holds information about a single function call argument. \n
 * This structure is used by the \a __MR_NODE_FUNC_CALL_T data structure.
 * @var mr_node_t __MR_NODE_CALL_ARG_T::value
 * Value of the argument.
 * @var mr_idx_t __MR_NODE_CALL_ARG_T::name
 * Starting index of the name. \n
 * If the name is not specified in the code, the \a name would be equal to <em>MR_INVALID_IDX</em>.
*/
struct __MR_NODE_CALL_ARG_T
{
    mr_node_t value;
    mr_idx_t name;
};
typedef struct __MR_NODE_CALL_ARG_T mr_node_call_arg_t;

/**
 * @struct __MR_NODE_FUNC_CALL_T
 * Data structure that holds information about a function call (with arguments).
 * @var mr_long_t __MR_NODE_FUNC_CALL_T::args
 * List of function call arguments.
 * @var mr_byte_t __MR_NODE_FUNC_CALL_T::size
 * Size of the \a args list.
 * @var mr_node_t __MR_NODE_FUNC_CALL_T::func
 * Function that needs to be called.
 * @var mr_idx_t __MR_NODE_FUNC_CALL_T::eidx
 * Ending index of the call.
*/
#pragma pack(push, 1)
struct __MR_NODE_FUNC_CALL_T
{
    mr_idx_t args;
    mr_byte_t size;
    mr_node_t func;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_FUNC_CALL_T mr_node_func_call_t;

/**
 * @struct __MR_NODE_EX_FUNC_CALL_T
 * Data structure that holds information about a function call (without argument).
 * @var mr_node_t __MR_NODE_EX_FUNC_CALL_T::func
 * Function that needs to be called.
 * @var mr_idx_t __MR_NODE_EX_FUNC_CALL_T::eidx
 * Ending index of the call.
*/
struct __MR_NODE_EX_FUNC_CALL_T
{
    mr_node_t func;
    mr_idx_t eidx;
};
typedef struct __MR_NODE_EX_FUNC_CALL_T mr_node_ex_func_call_t;

/**
 * @struct __MR_NODE_DOLLAR_METHOD_T
 * Data structure that holds information about a dollar method call (with arguments).
 * @var mr_long_t __MR_NODE_DOLLAR_METHOD_T::params
 * List of parameters.
 * @var mr_byte_t __MR_NODE_DOLLAR_METHOD_T::size
 * Size of the \a params list.
 * @var mr_idx_t __MR_NODE_DOLLAR_METHOD_T::name
 * Index of the name of dollar method.
 * @var mr_short_t __MR_NODE_DOLLAR_METHOD_T::sidx
 * Starting index of dollar method.
*/
#pragma pack(push, 1)
struct __MR_NODE_DOLLAR_METHOD_T
{
    mr_idx_t params;
    mr_byte_t size;
    mr_idx_t name;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_DOLLAR_METHOD_T mr_node_dollar_method_t;

/**
 * @struct __MR_NODE_EX_DOLLAR_METHOD_T
 * Data structure that holds information about a dollar method call (without argument).
 * @var mr_idx_t __MR_NODE_EX_DOLLAR_METHOD_T::name
 * Index of the name of dollar method.
 * @var mr_idx_t __MR_NODE_EX_DOLLAR_METHOD_T::sidx
 * Starting index of dollar method call.
*/
#pragma pack(push, 1)
struct __MR_NODE_EX_DOLLAR_METHOD_T
{
    mr_idx_t name;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_EX_DOLLAR_METHOD_T mr_node_ex_dollar_method_t;

/**
 * @struct __MR_NODE_IF_T
 * Data structure that holds information about an if statement (if).
 * @var mr_node_t __MR_NODE_IF_T::cond
 * Condition of the if statement.
 * @var mr_node_t __MR_NODE_IF_T::body
 * Body of the if statement.
 * @var mr_idx_t __MR_NODE_IF_T::sidx
 * Starting index of the if statement.
*/
#pragma pack(push, 1)
struct __MR_NODE_IF_T
{
    mr_node_t cond;
    mr_node_t body;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_IF_T mr_node_if_t;

/**
 * @struct __MR_NODE_IF_ELSE_T
 * Data structure that holds information about an if statement (if and else).
 * @var mr_node_t __MR_NODE_IF_ELSE_T::cond
 * Condition of the if statement.
 * @var mr_node_t __MR_NODE_IF_ELSE_T::body
 * Body of the if statement.
 * @var mr_node_t __MR_NODE_IF_ELSE_T::ebody
 * Body of the else statement.
 * @var mr_idx_t __MR_NODE_IF_ELSE_T::sidx
 * Statring index of the if statement.
*/
#pragma pack(push, 1)
struct __MR_NODE_IF_ELSE_T
{
    mr_node_t cond;
    mr_node_t body;
    mr_node_t ebody;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_IF_ELSE_T mr_node_if_else_t;

/**
 * @struct __MR_NODE_IF_ELIF_T
 * Data structure that holds information about an if statement (if, elif, and else).
 * @var mr_node_t __MR_NODE_IF_ELIF_T::ebody
 * Body of the else statement.
 * @var mr_idx_t __MR_NODE_IF_ELIF_T::cases
 * Cases of the if statement (if and elif).
 * @var mr_idx_t __MR_NODE_IF_ELIF_T::size
 * Size of the cases list.
 * @var mr_idx_t __MR_NODE_IF_ELIF_T::sidx
 * Starting index of the if statement.
*/
#pragma pack(push, 1)
struct __MR_NODE_IF_ELIF_T
{
    mr_node_t ebody;
    mr_idx_t cases;
    mr_idx_t size;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_IF_ELIF_T mr_node_if_elif_t;

/**
 * @struct __MR_NODE_SWITCH_T
 * Data structure that holds information about a switch statement (case).
 * @var mr_node_t __MR_NODE_SWITCH_T::value
 * Value of the switch statement.
 * @var mr_idx_t __MR_NODE_SWITCH_T::cases
 * Cases of the switch statement.
 * @var mr_idx_t __MR_NODE_SWITCH_T::size
 * Size of the cases list.
 * @var mr_idx_t __MR_NODE_SWITCH_T::sidx
 * Statring index of the switch statement.
 * @var mr_idx_t __MR_NODE_SWITCH_T::eidx
 * Ending index of the switch statement.
*/
#pragma pack(push, 1)
struct __MR_NODE_SWITCH_T
{
    mr_node_t value;
    mr_idx_t cases;
    mr_idx_t size;
    mr_idx_t sidx;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_SWITCH_T mr_node_switch_t;

/**
 * @struct __MR_NODE_SWITCH_DEF_T
 * Data structure that holds information about a switch statement (case and default).
 * @var mr_node_t __MR_NODE_SWITCH_DEF_T::value
 * Value of the switch statement.
 * @var mr_node_t __MR_NODE_SWITCH::dbody
 * Body of the default statement.
 * @var mr_idx_t __MR_NODE_SWITCH_DEF_T::cases
 * Cases of the switch statement.
 * @var mr_idx_t __MR_NODE_SWITCH_DEF_T::size
 * Size of the cases list.
 * @var mr_idx_t __MR_NODE_SWITCH_DEF_T::sidx
 * Statring index of the switch statement.
 * @var mr_idx_t __MR_NODE_SWITCH_DEF_T::eidx
 * Ending index of the switch statement.
*/
#pragma pack(push, 1)
struct __MR_NODE_SWITCH_DEF_T
{
    mr_node_t value;
    mr_node_t dbody;
    mr_idx_t cases;
    mr_idx_t size;
    mr_idx_t sidx;
    mr_idx_t eidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_SWITCH_DEF_T mr_node_switch_def_t;

/**
 * @struct __MR_NODE_IMPORT_T
 * Data structure that holds information about an import or an include statement.
 * @var mr_idx_t __MR_NODE_IMPORT_T::libs
 * The list of libraries.
 * @var mr_idx_t __MR_NODE_IMPORT_T::size
 * Size of the libraries list.
 * @var mr_idx_t __MR_NODE_IMPORT_T::sidx
 * Starting index of the list.
*/
#pragma pack(push, 1)
struct __MR_NODE_IMPORT_T
{
    mr_idx_t libs;
    mr_byte_t size;
    mr_idx_t sidx;
};
#pragma pack(pop)
typedef struct __MR_NODE_IMPORT_T mr_node_import_t;

/**
 * It extracts the starting index of a node.
 * @param node
 * The specified node.
 * @return It returns the starting index of the <em>node</em>.
*/
mr_long_t mr_node_sidx(
    mr_node_t node);

/**
 * It extracts the ending index of a node.
 * @param node
 * The specified node.
 * @return It returns the ending index of the <em>node</em>.
*/
mr_long_t mr_node_eidx(
    mr_node_t node);

#ifdef __MR_DEBUG__

/**
 * It prints out a node (only available in Debug builds).
 * @param node
 * The node that needs to be printed.
 */
void mr_node_print(
    mr_node_t node);

/**
 * It prints out a list of nodes (only available in Debug builds).
 * @param nodes
 * The list of nodes.
 * @param size
 * Size of the nodes list.
*/
void mr_node_prints(
    mr_node_t *nodes, mr_long_t size);

#endif

#endif
