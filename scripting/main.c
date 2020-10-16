#include "token.h"
#include "tokenizer.h"
#include "parser.h"
#include "ast.h"

int main() {
    tokenizer_t lexer = { 0 };
	//const char* source_code = "( [10, 20, 'hejsan'] )";
    const char* source_code = \
        "(" \
        "   foo = ['hej']," \
        "   bar = x" \
        ")";

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



program             := expression_list

expression_list     := '(' (expression (',' expression)*)? ')'
param_list          := '(' (identifier (',' identifier)*)? ')'
value_list          := '(' (value (',' value)*)? ')'

value_declaration   := identifier '=' value
function_call       := identifier value_list
func_declaration    := param_list '>' expression_list

identifier          := (character | '_') (character | digit | '_')*

value               :=  number_literal
                    |   string_literal
                    |   list_value
                    |   dict_value
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
string_literal      := '\'' .* '\''
number_literal      := digit+ ('.' digit+)?

*/