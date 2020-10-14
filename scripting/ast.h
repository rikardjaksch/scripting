#pragma once

typedef struct ast_node_t ast_node_t;

typedef struct ast_node_string_literal_t {
	char* value;
} ast_node_string_literal_t;

typedef struct ast_node_identifier_t {
	char* symbol;
} ast_node_identifier_t;

typedef struct ast_node_number_literal_t {
	double value;
} ast_node_number_literal_t;

typedef struct ast_node_list_value_t {
	ast_node_t** elements;
	unsigned num_elements;
} ast_node_list_value_t;

typedef struct ast_node_value_decl_t {
	ast_node_t* identifier;
	ast_node_t* value;
} ast_node_value_decl_t;

typedef struct ast_node_func_call_t {
	ast_node_t* identifier;
	ast_node_t** params;
} ast_node_func_call_t;

typedef struct ast_node_t {
	enum {
		AST_TYPE_STRING_LITERAL,
		AST_TYPE_NUMBER_LITERAL,
		AST_TYPE_LIST_VALUE,
		AST_TYPE_VALUE_DECL,
		AST_TYPE_FUNC_CALL,
		AST_TYPE_IDENTIFIER
	} type;

	union {
		ast_node_string_literal_t string_literal;
		ast_node_number_literal_t number_literal;
		ast_node_list_value_t list_value;
		ast_node_value_decl_t value_decl;
		ast_node_func_call_t func_call;
		ast_node_identifier_t identifier;
	};
} ast_node_t;

ast_node_t* ast_create_string_literal(const char* value);
ast_node_t* ast_create_number_literal(double value);
ast_node_t* ast_create_list_value();
ast_node_t* ast_create_identifier(const char* symbol);
ast_node_t* ast_create_value_decl();
ast_node_t* ast_create_func_call();