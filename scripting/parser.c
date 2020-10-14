#include "parser.h"
#include "tokenizer.h"
#include "token.h"
#include "ast.h"
#include "array.h"

#include <assert.h>

ast_node_t* parser_parse_string_literal(parser_t* parser);
ast_node_t* parser_parse_value(parser_t* parser);
ast_node_t* parser_parse_list_value(parser_t* parser);
ast_node_t* parser_parse_expression(parser_t* parser);
ast_node_t* parser_parse_expression_list(parser_t* parser);
ast_node_t* parser_parse_identifier(parser_t* parser);

void parser_initialize(parser_t* parser, tokenizer_t* tokenizer) {
	parser->tokenizer = tokenizer;
	tokenizer_next(tokenizer, &parser->current_token);
}

void parser_eat(parser_t* parser, token_type_e type) {
	if (parser->current_token.type == type) {
		tokenizer_next(parser->tokenizer, &parser->current_token);
	}
	else {
		assert(false && "Trying to eat token of wrong type");
	}
}

ast_node_t* parser_parse_string_literal(parser_t* parser) {
	ast_node_t* node = ast_create_string_literal(parser->current_token.lexeme);
	parser_eat(parser, TOKEN_TYPE_STRING_LITERAL);
	return node;
}

ast_node_t* parser_parse_value(parser_t* parser) {
	ast_node_t* node = 0;

	if (parser->current_token.type == TOKEN_TYPE_STRING_LITERAL) {
		return parser_parse_string_literal(parser);
	}
	else if (parser->current_token.type == TOKEN_TYPE_OPEN_BRACKET) {
		return parser_parse_list_value(parser);
	}

	return node;
}

ast_node_t* parser_parse_list_value(parser_t* parser) {
	parser_eat(parser, TOKEN_TYPE_OPEN_BRACKET);
	
	ast_node_t* node = ast_create_list_value();
	assert(node);

	while (parser->current_token.type != TOKEN_TYPE_CLOSE_BRACKET) {
		ast_node_t* element = parser_parse_value(parser);		
		array_push(node->list_value.elements, element);
		node->list_value.num_elements++;
		
		if (parser->current_token.type == TOKEN_TYPE_COMMA)
			parser_eat(parser, TOKEN_TYPE_COMMA);
	}

	parser_eat(parser, TOKEN_TYPE_CLOSE_BRACKET);
	return node;
}

ast_node_t* parser_parse_expression(parser_t* parser) {
	ast_node_t* identifier = parser_parse_identifier(parser);

	if (parser->current_token.type == TOKEN_TYPE_EQUALS) {
		parser_eat(parser, TOKEN_TYPE_EQUALS);
		ast_node_t* value = parser_parse_value(parser);

		ast_node_t* value_decl = ast_create_value_decl();
		value_decl->value_decl.identifier = identifier;
		value_decl->value_decl.value = value;
		return value_decl;
	}
	else if (parser->current_token.type == TOKEN_TYPE_OPEN_PAREN) {
		parser_eat(parser, TOKEN_TYPE_OPEN_PAREN);
	}

	return 0;
}

ast_node_t* parser_parse_expression_list(parser_t* parser) {
	return 0;
}

ast_node_t* parser_parse_identifier(parser_t* parser) {
	ast_node_t* node = ast_create_identifier(parser->current_token.lexeme);
	parser_eat(parser, TOKEN_TYPE_IDENTIFIER);
	return node;
}

ast_node_t* parser_parse(parser_t* parser) {
	return parser_parse_expression(parser);
}