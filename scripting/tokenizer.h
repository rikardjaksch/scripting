#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct token_t token_t;

typedef struct tokenizer_t {
	char* stream;
	size_t length;
	size_t position;

	size_t line_position;
	size_t line_number;
} tokenizer_t;

void tokenizer_initialize(tokenizer_t* lexer, const char* source);
void tokenizer_destruct(tokenizer_t* lexer);
bool tokenizer_has_next(tokenizer_t* lexer);
void tokenizer_next(tokenizer_t* lexer, token_t* token);