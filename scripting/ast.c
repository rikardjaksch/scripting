#include "ast.h"
#include "array.h"

#include <string.h>
#include <assert.h>

// Global list of all created nodes
ast_node_t** ast_nodes = 0;

ast_node_t* create_new_node(int type) {
	ast_node_t* node = (ast_node_t*)malloc(sizeof(ast_node_t));
	assert(node);
	array_push(ast_nodes, node);	
	node->type = type;
	return node;
}

ast_node_t* ast_create_string_literal(const char* value) {
	ast_node_t* node = create_new_node(AST_TYPE_STRING_LITERAL);

	size_t len = strlen(value);
	node->string_literal.value = malloc(len + 1);
	assert(node->string_literal.value);
	strcpy_s(node->string_literal.value, len + 1, value);

	return node;
}

ast_node_t* ast_create_number_literal(double value) {
	ast_node_t* node = create_new_node(AST_TYPE_NUMBER_LITERAL);

	node->number_literal.value = value;

	return node;
}

ast_node_t* ast_create_list_value() {
	ast_node_t* node = create_new_node(AST_TYPE_LIST_VALUE);
	
	node->list_value.elements = 0;
	node->list_value.num_elements = 0;

	return node;
}

ast_node_t* ast_create_identifier(const char* symbol) {
	ast_node_t* node = create_new_node(AST_TYPE_IDENTIFIER);

	size_t len = strlen(symbol);
	node->identifier.symbol = malloc(len + 1);
	assert(node->identifier.symbol);
	strcpy_s(node->identifier.symbol, len + 1, symbol);

	return node;
}

ast_node_t* ast_create_value_decl() {
	ast_node_t* node = create_new_node(AST_TYPE_VALUE_DECL);
	return node;
}

ast_node_t* ast_create_func_call() {
	ast_node_t* node = create_new_node(AST_TYPE_FUNC_CALL);
	return node;
}