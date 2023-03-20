%skeleton "lalr1.cc"
%require  "3.2"
%debug
%defines

%define api.namespace { alpha::syntax }
%define api.parser.class { Parser }

%code requires {
    namespace alpha {
    namespace syntax {
        class Scanner;
    }
    }
}

%parse-param { Scanner &scanner }

%code {
    #include <iostream>

    #undef yylex
    #define yylex scanner.yylex
}

%token      BAR

/* %locations */

%%

    FOO : BAR { std::cout << "hey" << std::endl; };

%%
