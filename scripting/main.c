#include "token.h"
#include "tokenizer.h"
#include "parser.h"
#include "ast.h"

int main() {
    tokenizer_t lexer = { 0 };
	//const char* source_code = "( [10, 20, 'hejsan'] )";
    const char* source_code = "test = 'hejsan'";

	tokenizer_initialize(&lexer, source_code);

    parser_t parser = { 0 };
    parser_initialize(&parser, &lexer);

    ast_node_t* root = parser_parse(&parser);
	
    // TODO: Free up parser, if needed, and all allocated ast-nodes

	// Free up lexer
	tokenizer_destruct(&lexer);
	return 0;
}



/*

typedef enum value_object_type_e {
    VALUE_TYPE_NUMBER,
    VALUE_TYPE_STRING,
    VALUE_TYPE_LIST,
    VALUE_TYPE_DICT,
    VALUE_TYPE_FUNC,
    VALUE_TYPE_NIL
} value_object_type_e;

typedef struct value_object_t {
    // Type of value this object holds
    value_object_type_e type;
    // Number of references to this object
    uint32_t references;

    union {
        double number;
        char* string;
        struct value_object_t* list;
        struct hash_map_t* hash;
        function_ptr* func;
    };
} value_object_t;



program             := expression_list

expression_list     := '(' (expression (',' expression)*)? ')'
param_list          := '(' (param_value (',' param_value)*)? ')'
value_list          := '(' (value (',' value)*)? ')'

value_declaration   := identifier '=' value
function_call       := identifier value_list
func_declaration    := param_list '->' expression_list

identifier          := (character | '_') (character | digit | '_')*

value               :=  number_literal
                    |   string_literal
                    |   list_value
                    |   dict_value
                    |   expression_list
                    |   function_call
                    |   function_decl
                    |   identifier

param_value         :=  number_literal
                    |   string_literal
                    |   list_value
                    |   dict_value
                    |   function_call
                    |   identifier

expression          :=  value_declaration
                    |   function_call


list_value          := '[' (value (',' value)*)? ']'


(
    foo = 10,
    foo,
    bar(x)
)



*/