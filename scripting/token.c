#include "token.h"

#include <string.h>
#include <stdio.h>

void token_initialize(token_t* token) {
	token->lexeme_length = 0;
	memset(token->lexeme, 0, MAX_TOKEN_LEXEME_LENGTH);
	token->position = 0;
	token->line_position = 0;
	token->line_number = 0;
	token->type = TOKEN_TYPE_UNKNOWN_CHARACTER;
}

const char* token_type_name(token_type_e type) {
	switch (type) {
	case TOKEN_TYPE_END_OF_STREAM:
		return "end_of_stream";
	case TOKEN_TYPE_OPEN_PAREN:
		return "open_paren";
	case TOKEN_TYPE_CLOSE_PAREN:
		return "close_paren";
	case TOKEN_TYPE_OPEN_BRACKET:
		return "open_bracket";
	case TOKEN_TYPE_CLOSE_BRACKET:
		return "close_bracket";
	case TOKEN_TYPE_SEMI_COLON:
		return "semi_colon";
	case TOKEN_TYPE_COMMA:
		return "comma";
	case TOKEN_TYPE_EQUALS:
		return "equals";
	case TOKEN_TYPE_NUMBER_LITERAL:
		return "number_literal";
	case TOKEN_TYPE_STRING_LITERAL:
		return "string_literal";
	case TOKEN_TYPE_IDENTIFIER:
		return "identifier";
	case TOKEN_TYPE_UNKNOWN_CHARACTER:
		return "unknown_character";
	default:
		return "not_implemented";
	}
}

void token_print(token_t* token) {
	printf("(%Iu, %Iu) %s - %s\n", token->line_position, token->line_number, token_type_name(token->type), token->lexeme);
}

void token_append_character(token_t* token, char c) {
	token->lexeme[token->lexeme_length++] = c;
}