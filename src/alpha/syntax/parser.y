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

PROGRAM :	/* empty */			{ print_derivation("PROGRAM", "empty"); }
		|	stmt PROGRAM		{ print_derivation("PROGRAM", "stmt PROGRAM"); }
        ;

stmt	:	expr SEMICOLON		{ print_derivation("stmt", "expr SEMICOLON"); }
	 	|	ifstmt				{ print_derivation("stmt", "ifstmt"); }
		|	whilestmt			{ print_derivation("stmt", "whilestmt"); }
		|	forstmt				{ print_derivation("stmt", "forstmt"); }
		|	returnstmt			{ print_derivation("stmt", "returnstmt"); }
		|	BREAK SEMICOLON		{ print_derivation("stmt", "BREAK SEMICOLON"); }
		|	CONTINUE SEMICOLON	{ print_derivation("stmt", "CONTINUE SEMICOLON"); }
		|	block				{ print_derivation("stmt", "block"); }
		|	funcdef				{ print_derivation("stmt", "funcdef"); }
		|	SEMICOLON			{ print_derivation("stmt", "SEMICOLON"); }
		;

expr	:	assignexpr			{ print_derivation("expr", "assignexpr"); }
		|	expr op expr		{ print_derivation("expr", "expr op expr"); }
		|	term				{ print_derivation("expr", "term"); }
		;

op		:	PLUS				{ print_derivation("op", "PLUS"); }
		|	MINUS				{ print_derivation("op", "MINUS"); }
		|	STAR				{ print_derivation("op", "STAR"); }
		|	DIV					{ print_derivation("op", "DIV"); }
		|	MOD					{ print_derivation("op", "MOD"); }
		|	GREATER				{ print_derivation("op", "GREATER"); }
		|	GREATER_EQUALS		{ print_derivation("op", "GREATER_EQUALS"); }
		|	LESS				{ print_derivation("op", "LESS"); }
		|	LESS_EQUALS			{ print_derivation("op", "LESS_EQUALS"); }
		|	EQUALS				{ print_derivation("op", "EQUALS"); }
		|	NOT_EQUALS			{ print_derivation("op", "NOT_EQUALS"); }
		|	AND					{ print_derivation("op", "AND"); }
		|	OR					{ print_derivation("op", "OR"); }
		;


/* END OF NICK SECTION */


/* ********************** */


/* START OF ALEX SECTION */

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
