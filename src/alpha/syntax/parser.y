%skeleton "lalr1.cc"
%require  "3.2"
%debug
%defines

%define api.namespace { alpha::syntax }
%define api.parser.class { Parser }

%code requires {
    namespace alpha {
    namespace lex {
        class Scanner;
    }
    }
}

%parse-param { alpha::lex::Scanner &scanner }

%locations
%define api.location.file "../../../include/alpha/syntax/location.h"
%define api.location.include {<alpha/syntax/location.h>}

%code {
    #include <iostream>

    #include <alpha/lex/scanner.h>

    #undef yylex
    #define yylex scanner.yylex

    static void print_derivation(const std::string&, const std::string&);
}

%token END_OF_FILE 0 "end of file"
%token INTEGER
%token FLOAT
%token STRING
%token IDENTIFIER
%token ONE_LINE_COMMENT
%token BLOCK_COMMENT
%token IF
%token ELSE
%token WHILE
%token FOR
%token FUNCTION
%token RETURN
%token BREAK
%token CONTINUE
%token AND
%token NOT
%token OR
%token LOCAL
%token TRUE
%token FALSE
%token NIL
%token ASSIGN               /*| =  |*/
%token PLUS                 /*| +  |*/
%token MINUS                /*| -  |*/
%token STAR                 /*| *  |*/
%token DIV                  /*| /  |*/
%token MOD                  /*| %  |*/
%token EQUALS               /*| == |*/
%token NOT_EQUALS           /*| != |*/
%token PLUS_PLUS            /*| ++ |*/
%token MINUS_MINUS          /*| -- |*/
%token GREATER              /*| >  |*/
%token LESS                 /*| <  |*/
%token GREATER_EQUALS       /*| >= |*/
%token LESS_EQUALS          /*| <= |*/
%token LEFT_CURLY_BRACKET   /*| {  |*/
%token RIGHT_CURLY_BRACKET  /*| }  |*/
%token LEFT_SQUARE_BRACKET  /*| [  |*/
%token RIGHT_SQUARE_BRACKET /*| ]  |*/
%token LEFT_PARENTHESIS     /*| (  |*/
%token RIGHT_PARENTHESIS    /*| )  |*/
%token SEMICOLON            /*| ;  |*/
%token COMMA                /*| ,  |*/
%token COLON                /*| :  |*/
%token DOUBLE_COLON         /*| :: |*/
%token DOT                  /*| .  |*/
%token DOUBLE_DOT           /*| .. |*/

/* %locations */

%start PROGRAM

%%

PROGRAM :   foo
        ;

foo     :   INTEGER         { print_derivation("foo", "INTEGER"); }
        |   foo INTEGER     { print_derivation("foo", "foo, INTEGER"); }
        ;


/*
 * WARNING! WRITE CODE ONLY IN YOUR
 * SECTION IN ORDER TO AVOID CONFLICTS.
 */

/* START OF NICK SECTION */

/* END OF NICK SECTION */


/* ********************** */


/* START OF ALEX SECTION */

call        :   call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS                                       {}
            |   lvalue  callsuffix                                                                  {}
            |   LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {}
            ;

callsuffix  :   normcall    {}
            |   methodcall  {}
            ;

normcall    :   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {}
            ;

methodcall  :   DOUBLE_DOT IDENTIFIER LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  {}
            ;

elist       :   /* empty */    {}
            |   expr elist_opt {}
            ;

elist_opt   :   /* empty */          {}
            |   COMMA expr elist_opt {}
            ;

objectdef   :   LEFT_SQUARE_BRACKET elist RIGHT_SQUARE_BRACKET   {}
            |   LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {}
            ;

/* END OF ALEX SECTION */

%%

static void print_derivation(const std::string& non_final, const std::string& final) {
    std::cout << non_final << "\t\t -> \t" << final << std::endl;
}

void
alpha::syntax::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
