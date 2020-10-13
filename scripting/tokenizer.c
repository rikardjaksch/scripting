#include "tokenizer.h"
#include "token.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>

bool is_character(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
bool is_digit(char c) { return (c >= '0' && c <= '9'); }
bool is_identifier_start_char(char c) { return is_character(c) || c == '_'; }
bool is_identifier_char(char c) { return is_identifier_start_char(c) || is_digit(c); }
bool is_whitespace(char c) { return c == ' ' || c == '\t'; }
bool is_single_char_token(char c) { return c == '(' || c == ')' || c == '[' || c == ']' || c == ';' || c == ',' || c == '='; }

void tokenizer_initialize(tokenizer_t* lexer, const char* source) {
	lexer->length = strlen(source);
	lexer->stream = (char*)malloc(lexer->length + 1);
	assert(lexer->stream);
	strcpy_s(lexer->stream, lexer->length + 1, source);
}

void tokenizer_destruct(tokenizer_t* lexer) {
	free(lexer->stream);
}

bool tokenizer_has_next(tokenizer_t* lexer) {
	return lexer->position < lexer->length;
}

void tokenizer_next(tokenizer_t* lexer, token_t* token) {
	token_initialize(token);

	// Just to make sure that we don't go past the end of the stream
	if (lexer->position >= lexer->length) {
		token->type = TOKEN_TYPE_END_OF_STREAM;
		return;
	}

	char current = lexer->stream[lexer->position];

	// Skip any whitespace
	while (is_whitespace(current) && lexer->position < lexer->length) {
		lexer->line_position++;

		current = lexer->stream[++lexer->position];
	}

	token->position = lexer->position;
	token->line_position = lexer->line_position;
	token->line_number = lexer->line_number;

	// Tokenize string literals
	if (current == '\'') {
		token->type = TOKEN_TYPE_STRING_LITERAL;

		lexer->position++;
		lexer->line_position++;
		current = lexer->stream[lexer->position];

		while (current != '\'') {
			// TODO: Handle special characters like \n, \t etc
			token_append_character(token, current);

			lexer->position++;
			lexer->line_position++;

			current = lexer->stream[lexer->position];
		}
		// Chomp last single quote
		lexer->position++;
		lexer->line_position++;
	} // Tokenize numbers
	else if (is_digit(current)) {
		token->type = TOKEN_TYPE_NUMBER_LITERAL;

		while (is_digit(current)) {
			token_append_character(token, current);

			lexer->position++;
			lexer->line_position++;

			current = lexer->stream[lexer->position];
		}		
	} // Tokenize identifiers
	else if (is_identifier_start_char(current)) {
		token->type = TOKEN_TYPE_IDENTIFIER;

		while (is_identifier_char(current)) {
			token_append_character(token, current);

			lexer->position++;
			lexer->line_position++;

			current = lexer->stream[lexer->position];
		}
	} // Tokenize single character tokens
	else if (is_single_char_token(current)) {
		switch (current) {
		case '(': token->type = TOKEN_TYPE_OPEN_PAREN; break;
		case ')': token->type = TOKEN_TYPE_CLOSE_PAREN; break;
		case '[': token->type = TOKEN_TYPE_OPEN_BRACKET; break;
		case ']': token->type = TOKEN_TYPE_CLOSE_BRACKET; break;
		case ';': token->type = TOKEN_TYPE_SEMI_COLON; break;
		case ',': token->type = TOKEN_TYPE_COMMA; break;
		case '=': token->type = TOKEN_TYPE_EQUALS; break;
		}

		token_append_character(token, current);
		lexer->position++;
		lexer->line_position++;
	}
	else {
		// Catch any unknown characters here
		lexer->position++;
		lexer->line_position++;
	}
}