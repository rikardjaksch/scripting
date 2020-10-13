#include "token.h"
#include "tokenizer.h"

int main() {
	tokenizer_t lexer = { 0 };
	const char* source_code = "( [10, 20, 'hejsan'] )";

	tokenizer_initialize(&lexer, source_code);

	// Lex all tokens until we run in to end of stream
	token_t token = { 0 };
	while (tokenizer_has_next(&lexer)) {
		tokenizer_next(&lexer, &token);
		token_print(&token);
	}

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
expression_list     := '(' expression* ')'

param_list          := '(' (param_value (',' param_value)*)? ')'
value_list          := '(' (value (',' value)*)? ')'

value_declaration   := identifier '=' value
func_declaration    := '(' param_list ')' '->' expression_list
function_call       := identifier '(' (value (',' value)*)? ')'

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

expression          :=  value_declaration ';'
                    |   function_call ';'
                    |   func_declaration ';'


list_value          := '[' (value (',' value)*)? ']'


(
    foo = (nil, b, c) -> (
        add([a, b, c])
    ),
    
    (10)
)



*/