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

%right      ASSIGN
%left       OR
%left       AND
%nonassoc   EQUALS              NOT_EQUALS
%nonassoc   GREATER             GREATER_EQUALS      LESS        LESS_EQUALS
%left       PLUS                MINUS
%left       STAR                DIV                 MOD
%right      NOT                 PLUS_PLUS           MINUS_MINUS UMINUS
%left       DOT                 DOUBLE_DOT
%left       LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%left       LEFT_PARENTHESIS    RIGHT_PARENTHESIS

%%

/*
 * WARNING! WRITE CODE ONLY IN YOUR
 * SECTION IN ORDER TO AVOID CONFLICTS.
 */

/* START OF NICK SECTION */

PROGRAM     :    /* empty */ { print_derivation("PROGRAM", "empty"); }
            |   stmt PROGRAM { print_derivation("PROGRAM", "stmt PROGRAM"); }
            ;

stmt        :   expr SEMICOLON     { print_derivation("stmt", "expr ;"); }
            |   ifstmt             { print_derivation("stmt", "ifstmt"); }
            |   whilestmt          { print_derivation("stmt", "whilestmt"); }
            |   forstmt            { print_derivation("stmt", "forstmt"); }
            |   returnstmt         { print_derivation("stmt", "returnstmt"); }
            |   BREAK SEMICOLO     { print_derivation("stmt", "BREAK ;"); }
            |   CONTINUE SEMICOLON { print_derivation("stmt", "CONTINUE ;"); }
            |   block              { print_derivation("stmt", "block"); }
            |   funcdef            { print_derivation("stmt", "funcdef"); }
            |   SEMICOLON          { print_derivation("stmt", ";"); }
            ;

expr        :   assignexpr   { print_derivation("expr", "assignexpr"); }
            |   expr op expr { print_derivation("expr", "expr op expr"); }
            |   term         { print_derivation("expr", "term"); }
            ;

op          :   PLUS           { print_derivation("op", "+"); }
            |   MINUS          { print_derivation("op", "-"); }
            |   STAR           { print_derivation("op", "*"); }
            |   DIV            { print_derivation("op", "/"); }
            |   MOD            { print_derivation("op", "%"); }
            |   GREATER        { print_derivation("op", ">"); }
            |   GREATER_EQUALS { print_derivation("op", ">="); }
            |   LESS           { print_derivation("op", "<"); }
            |   LESS_EQUALS    { print_derivation("op", "<="); }
            |   EQUALS         { print_derivation("op", "=="); }
            |   NOT_EQUALS     { print_derivation("op", "!="); }
            |   AND            { print_derivation("op", "AND"); }
            |   OR             { print_derivation("op", "OR"); }
            ;

term        :   LEFT_PARENTHESIS expr RIGHT_PARENTHESIS { print_derivation("term", "( expr )"); }
            |   MINUS expr                 %prec UMINUS { print_derivation("term", "- expr"); }
            |   NOT expr                                { print_derivation("term", "NOT expr"); }
            |   PLUS_PLUS lvalue                        { print_derivation("term", "++ lvalue"); }
            |   lvalue PLUS_PLUS                        { print_derivation("term", "lvalue ++"); }
            |   MINUS_MINUS lvalue                      { print_derivation("term", "-- lvalue"); }
            |   lvalue MINUS_MINUS                      { print_derivation("term", "lvalue --"); }
            |   primary                                 { print_derivation("term", "primary"); }
            ;

assignexpr  :   lvalue ASSIGN expr { print_derivation("assignexpr", "lvalue = expr"); }
            ;

primary     :   lvalue                                      { print_derivation("primary", "lvalue"); }
            |   call                                       { print_derivation("primary", "call"); }
            |   objectdef                                  { print_derivation("primary", "objectdef"); }
            |   LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS { print_derivation("primary", "( funcdef )"); }
            |   const                                      { print_derivation("primary", "const"); }
            ;

lvalue      :   IDENTIFIER              { print_derivation("lvalue", "IDENTIFIER"); }
            |   LOCAL IDENTIFIER        { print_derivation("lvalue", "LOCAL IDENTIFIER"); }
            |   DOUBLE_COLON IDENTIFIER { print_derivation("lvalue", ":: IDENTIFIER"); }
            |   member                  { print_derivation("lvalue", "member"); }
            ;

member      :   lvalue DOT IDENTIFIER                                { print_derivation("member", "lvalue . IDENTIFIER"); }
            |   lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET { print_derivation("member", "lvalue [ expr ]"); }
            |   call DOT IDENTIFIER                                  { print_derivation("member", "call . IDENTIFIER"); }
            |   call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET   { print_derivation("member", "call [ expr ]"); }
            ;


/* END OF NICK SECTION */


/* ********************** */


/* START OF ALEX SECTION */

call        :   call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS                                       { print_derivation("call", "call ( elist )"); }
            |   lvalue  callsuffix                                                                  { print_derivation("call", "lvalue callsuffix"); }
            |   LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { print_derivation("call", "( funcdef ) ( elist )"); }
            ;

callsuffix  :   normcall    { print_derivation("callsuffix", "normcall"); }
            |   methodcall  { print_derivation("callsuffix", "methodcall"); }
            ;

normcall    :   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { print_derivation("normcall", "( elist )"); }
            ;

methodcall  :   DOUBLE_DOT IDENTIFIER LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  { print_derivation("methodcall", ".. IDENTIFIER ( elist )"); }
            ;

elist       :   /* empty */    { print_derivation("elist", "empty"); }
            |   expr elist_opt { print_derivation("elist", "expr elist_opt"); }
            ;

elist_opt   :   /* empty */          { print_derivation("elist_opt", "empty"); }
            |   COMMA expr elist_opt { print_derivation("elist_opt", ", expr elist_opt"); }
            ;

objectdef   :   LEFT_SQUARE_BRACKET elist RIGHT_SQUARE_BRACKET   { print_derivation("objectdef", "[ elist ]"); }
            |   LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET { print_derivation("objectdef", "[ indexed ]"); }
            ;

indexed     :   /* empty */             { print_derivation("indexed", "empty"); }
            |   indexedelem indexed_opt { print_derivation("indexed", "indexedelem indexed_opt"); }
            ;

indexed_opt :   /* empty */                   { print_derivation("indexed_opt", "empty"); }
            |   COMMA indexedelem indexed_opt { print_derivation("indexed_opt", ", indexedelem indexed_opt"); }
            ;

indexedelem :   LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET { print_derivation("indexedelem", "{ expr : expr }"); }
            ;

block       :   LEFT_SQUARE_BRACKET block_opt RIGHT_CURLY_BRACKET { print_derivation("block", "{ block_opt }"); }
            ;

block_opt   :   /* empty */    { print_derivation("block_opt", "empty"); }
            |   stmt block_opt { print_derivation("block_opt", "stmt block_opt"); }
            ;

funcdef     :   FUNCTION LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block            { print_derivation("funcdef", "FUNCTION ( idlist ) block"); }
            |   FUNCTION IDENTIFIER LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block { print_derivation("funcdef", "FUNCTION IDENTIFIER ( idlist ) block"); }
            ;

const       :   INTEGER { print_derivation("const", "INTEGER"); }
            |   FLOAT   { print_derivation("const", "FLOAT"); }
            |   STRING  { print_derivation("const", "STRING"); }
            |   NIL     { print_derivation("const", "NIL"); }
            |   TRUE    { print_derivation("const", "TRUE"); }
            |   FALSE   { print_derivation("const", "FALSE"); }
            ;

idlist      :   /* empty */           { print_derivation("idlist", "empty"); }
            |   IDENTIFIER idlist_opt { print_derivation("idlist", "IDENTIFIER idlist_opt"); }
            ;

idlist_opt  :   /* empty */             { print_derivation("idlist_opt", "empty"); }
            |   COMMA IDENTIFIER idlist { print_derivation("idlist_opt", ", IDENTIFIER idlist"); }
            ;

ifstmt      :   IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt           { print_derivation("ifstmt", "IF ( expr ) stmt"); }
            |   IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt { print_derivation("ifstmt", "IF ( expr ) stmt ELSE stmt"); }
            ;

whilestmt   :   WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt { print_derivation("whilestmt", "WHILE ( expr ) stmt"); }
            ;

forstmt     :   FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt { print_derivation("forstmt", "FOR ( elist ; expr ; elist ) stmt"); }
            ;

returnstmt  :   RETURN SEMICOLON      { print_derivation("returnstmt", "RETURN ;"); }
            |   RETURN expr SEMICOLON { print_derivation("returnstmt", "RETURN expr ;"); }
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
