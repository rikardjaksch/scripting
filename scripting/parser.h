#pragma once

#include "token.h"

typedef struct token_t token_t;
typedef struct tokenizer_t tokenizer_t;
typedef struct ast_node_t ast_node_t;

typedef struct parser_t {
	tokenizer_t* tokenizer;
	token_t current;
	token_t next;
} parser_t;


void parser_initialize(parser_t* parser, tokenizer_t* tokenizer);
ast_node_t* parser_parse(parser_t* parser);