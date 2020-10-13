#pragma once

typedef enum token_type_e {
	TOKEN_TYPE_END_OF_STREAM,
	TOKEN_TYPE_OPEN_PAREN,
	TOKEN_TYPE_CLOSE_PAREN,
	TOKEN_TYPE_OPEN_BRACKET,
	TOKEN_TYPE_CLOSE_BRACKET,
	TOKEN_TYPE_SEMI_COLON,
	TOKEN_TYPE_COMMA,
	TOKEN_TYPE_EQUALS,
	TOKEN_TYPE_NUMBER_LITERAL,
	TOKEN_TYPE_STRING_LITERAL,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_UNKNOWN_CHARACTER
} token_type_e;

#define MAX_TOKEN_LEXEME_LENGTH 256

typedef struct token_t {
	token_type_e type;
	char lexeme[MAX_TOKEN_LEXEME_LENGTH];
	unsigned lexeme_length;

	unsigned position;
	unsigned line_position;
	unsigned line_number;
} token_t;

void token_initialize(token_t* token);
void token_print(token_t* token);
void token_append_character(token_t* token, char c);


