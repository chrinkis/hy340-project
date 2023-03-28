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

    #include <alpha/symbol/table.h>

    using SearchResult = alpha::symbol::Table::SearchResult;
}

%parse-param { alpha::lex::Scanner &scanner }

%locations
%define api.location.include {<alpha/syntax/location.h>}

%code {
    #include <iostream>
    #include <cassert>

    #include <alpha/lex/scanner.h>
    #include <alpha/symbol/table.h>

    #undef yylex
    #define yylex scanner.yylex

    static void print_derivation(const std::string&, const std::string&);
}

/* color codes for defualt and error messages */
%code {
#define SET_COLOR_FOR_ERROR "\033[31m"
#define RESET_COLOR         "\033[0m"
}

/* Insert variables and search (and check usage of) symbols */
%code {

/* local */
#define S_TABLE_SEARCH_AND_ADD_LOCAL_VAR(name, lvalue, location)       \
  {                                                                    \
    lvalue = symbol_table.search_for_visible_local_symbol(name);       \
                                                                       \
    switch (lvalue) {                                                  \
      case SearchResult::MUTABLE:                                      \
        break;                                                         \
                                                                       \
      case SearchResult::UNMUTABLE:                                    \
        break;                                                         \
                                                                       \
      case SearchResult::NOT_FOUND:                                    \
                                                                       \
        if (symbol_table.can_add_local_variable(name)) {               \
          symbol_table.add_local_variable(name, location);             \
          lvalue = SearchResult::MUTABLE;                              \
        } else {                                                       \
          std::cerr << SET_COLOR_FOR_ERROR                             \
                    << "error with local variable \"" << name          \
                    << "\" shadowing a library function" << std::endl  \
                    << RESET_COLOR;                                    \
        }                                                              \
        break;                                                         \
                                                                       \
      default:                                                         \
        assert(0);                                                     \
    }                                                                  \
  }

/* global */
#define S_TABLE_SEARCH_GLOBAL_VAR(name, lvalue)                        \
  {                                                                    \
    lvalue = symbol_table.search_for_visible_global_symbol(name);      \
                                                                       \
    switch (lvalue) {                                                  \
      case SearchResult::MUTABLE:                                      \
        break;                                                         \
                                                                       \
      case SearchResult::UNMUTABLE:                                    \
        break;                                                         \
                                                                       \
      case SearchResult::NOT_FOUND:                                    \
                                                                       \
        std::cerr << SET_COLOR_FOR_ERROR                               \
                  << "error finding global variable or function "      \
                  << "with name \"" << name << "\"" << std::endl       \
                  << RESET_COLOR;                                      \
                                                                       \
        break;                                                         \
                                                                       \
      default:                                                         \
        assert(0);                                                     \
    }                                                                  \
  }

/* none (for current visible scope) */
#define S_TABLE_SEARCH_AND_ADD_VAR(name, lvalue, location)             \
  {                                                                    \
    lvalue = symbol_table.search_for_visible_symbol(name);             \
                                                                       \
    switch (lvalue) {                                                  \
      case SearchResult::MUTABLE:                                      \
        break;                                                         \
                                                                       \
      case SearchResult::UNMUTABLE:                                    \
        break;                                                         \
                                                                       \
      case SearchResult::NOT_FOUND:                                    \
                                                                       \
        if (symbol_table.can_add_variable(name)) {                     \
          symbol_table.add_variable(name, location);                   \
          lvalue = SearchResult::MUTABLE;                              \
        } else {                                                       \
          std::cerr << SET_COLOR_FOR_ERROR                             \
                    << "error accessing a variable or function "       \
                    << "with name \"" << name << "\" that is not "     \
                    << "visible" << std::endl                          \
                    << RESET_COLOR;                                    \
        }                                                              \
                                                                       \
        break;                                                         \
                                                                       \
      default:                                                         \
        assert(0);                                                     \
    }                                                                  \
  }

/* Handle function symbol errors     */
/* `type_of_symbol` : `SearchResult` */
/* `usage_info` : string for the possible error message */
#define S_TABLE_CHECK_FUNCTION_ERRORS(type_of_symbol, usage_info)      \
  {                                                                    \
    if (type_of_symbol == SearchResult::UNMUTABLE) {                   \
      std::cerr << SET_COLOR_FOR_ERROR                                 \
                << "error: cannot perform " << usage_info              \
                << " a function" << std::endl                          \
                << RESET_COLOR;                                        \
    }                                                                  \
  }

/* For when we need to further check a symbol's usage */
#define S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED(type_of_symbol, next_symbol) \
  { next_symbol = type_of_symbol; }

/* For when we don't need to further check a symbol's usage */
#define S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED(next_symbol)              \
  { next_symbol = SearchResult::NOT_FOUND; }

}

/* Symbol table handles for functions */
%code {

#define S_TABLE_FUNC_START(name, location)               \
  {                                                      \
    if (symbol_table.can_add_function(name)) {           \
      symbol_table.start_function(name, location);       \
    } else {                                             \
      std::cerr << SET_COLOR_FOR_ERROR                   \
                << "error inserting function \"" << name \
                << "\" in Symbol Table" << std::endl     \
                << RESET_COLOR;                          \
      S_TABLE_FUNC_START_ANONYMOYS                       \
    }                                                    \
  }

#define S_TABLE_FUNC_START_ANONYMOYS(location) \
  { symbol_table.start_function(location); }

#define S_TABLE_FUNC_END \
  { symbol_table.end_function(); }

}

/* Handle code block entry and exit */
%code {

#define S_TABLE_BLOCK_ENTER { symbol_table.increase_scope(); }

#define S_TABLE_BLOCK_EXIT  { symbol_table.decrease_scope(); }

}

/* Symbol table handles for formal arguments */
%code {

#define S_TABLE_ADD_ARG(name, location)                  \
  {                                                      \
    if (symbol_table.can_add_argument(name)) {           \
      symbol_table.add_argument(name, location);         \
    } else {                                             \
      std::cerr << SET_COLOR_FOR_ERROR                   \
                << "error inserting argument \"" << name \
                << "\" in Symbol Table" << std::endl     \
                << RESET_COLOR;                          \
    }                                                    \
  }

#define S_TABLE_END_LIST_ARG()                           \
  {                                                      \
      symbol_table.end_argument_list();                  \
  }

}

/* The grammar expects 1 shift/reduce conflict (ifstmt) */
%expect 1

/* For token types */
%define api.value.type variant

%token END_OF_FILE 0 "end of file"
%token <int> INTEGER
%token <float> FLOAT
%token <std::string> STRING
%token <std::string> IDENTIFIER
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

%type <SearchResult> lvalue
%type <SearchResult> member
%type <SearchResult> assignexpr
%type <SearchResult> primary
%type <SearchResult> term
%type <SearchResult> expr

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

PROGRAM     :   %empty       { print_derivation("PROGRAM", "empty"); }
            |   stmt PROGRAM { print_derivation("PROGRAM", "stmt PROGRAM"); }
            ;

stmt        :   expr SEMICOLON     { print_derivation("stmt", "expr ;"); }
            |   ifstmt             { print_derivation("stmt", "ifstmt"); }
            |   whilestmt          { print_derivation("stmt", "whilestmt"); }
            |   forstmt            { print_derivation("stmt", "forstmt"); }
            |   returnstmt         { print_derivation("stmt", "returnstmt"); }
            |   BREAK SEMICOLON    { print_derivation("stmt", "BREAK ;"); }
            |   CONTINUE SEMICOLON { print_derivation("stmt", "CONTINUE ;"); }
            |   block              { print_derivation("stmt", "block"); }
            |   funcdef            { print_derivation("stmt", "funcdef"); }
            |   SEMICOLON          { print_derivation("stmt", ";"); }
            ;

expr        :   assignexpr               { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "assignexpr");
                                         }
            |   expr PLUS expr           { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"+\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"+\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr + expr");
                                         }
            |   expr MINUS expr          { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"-\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"-\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr - expr");
                                         }
            |   expr STAR expr           { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"*\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"*\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr * expr");
                                         }
            |   expr DIV expr            { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"/\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"/\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr / expr");
                                         }
            |   expr MOD expr            { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"%\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"%\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr % expr");
                                         }
            |   expr GREATER expr        { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\">\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\">\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr > expr");
                                         }
            |   expr GREATER_EQUALS expr { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\">=\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\">=\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr >= expr");
                                         }
            |   expr LESS expr           { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"<\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"<\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr < expr");
                                         }
            |   expr LESS_EQUALS expr    { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"<=\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"<=\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr <= expr");
                                         }
            |   expr EQUALS expr         { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"==\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"==\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr == expr");
                                         }
            |   expr NOT_EQUALS expr     { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"!=\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"!=\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr != expr");
                                         }
            |   expr AND expr            { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"AND\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"AND\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr AND expr");
                                         }
            |   expr OR expr             { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"OR\" with");
                                           S_TABLE_CHECK_FUNCTION_ERRORS($3, "\"OR\" with");
                                           S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                           print_derivation("expr", "expr OR expr");
                                         }
            |   term                     { S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED($1, $$);
                                           print_derivation("expr", "term");
                                         }
            ;

term        :   LEFT_PARENTHESIS expr RIGHT_PARENTHESIS { S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED($2, $$);
                                                          print_derivation("term", "( expr )");
                                                        }
            |   MINUS expr                 %prec UMINUS { S_TABLE_CHECK_FUNCTION_ERRORS($2, "unary \"-\" with");
                                                          S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                          print_derivation("term", "- expr");
                                                        }
            |   NOT expr                                { S_TABLE_CHECK_FUNCTION_ERRORS($2, "\"NOT\" with");
                                                          S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                          print_derivation("term", "NOT expr");
                                                        }
            |   PLUS_PLUS lvalue                        { S_TABLE_CHECK_FUNCTION_ERRORS($2, "\"++\" with");
                                                          S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                          print_derivation("term", "++ lvalue");
                                                        }
            |   lvalue PLUS_PLUS                        { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"++\" with");
                                                          S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                          print_derivation("term", "lvalue ++");
                                                        }
            |   MINUS_MINUS lvalue                      { S_TABLE_CHECK_FUNCTION_ERRORS($2, "\"--\" with");
                                                          S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                          print_derivation("term", "-- lvalue");
                                                        }
            |   lvalue MINUS_MINUS                      { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"--\" with");
                                                          S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                          print_derivation("term", "lvalue --");
                                                        }
            |   primary                                 { S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED($1, $$);
                                                          print_derivation("term", "primary");
                                                        }
            ;

assignexpr  :   lvalue ASSIGN expr { S_TABLE_CHECK_FUNCTION_ERRORS($1, "assignment to");
                                     S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                     print_derivation("assignexpr", "lvalue = expr");
                                   }
            ;

primary     :   lvalue                                     { S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED($1, $$);
                                                             print_derivation("primary", "lvalue");
                                                           }
            |   call                                       { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                             print_derivation("primary", "call");
                                                           }
            |   objectdef                                  { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                             print_derivation("primary", "objectdef");
                                                           }
            |   LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS { S_TABLE_FURTHER_SYMBOL_CHECK_NEEDED(SearchResult::UNMUTABLE, $$);
                                                             print_derivation("primary", "( funcdef )");
                                                           }
            |   const                                      { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                             print_derivation("primary", "const");
                                                           }
            ;

lvalue      :   IDENTIFIER              { S_TABLE_SEARCH_AND_ADD_VAR($1,$$,@1);
                                          print_derivation("lvalue", "IDENTIFIER"); 
                                        }
            |   LOCAL IDENTIFIER        { S_TABLE_SEARCH_AND_ADD_LOCAL_VAR($2,$$,@2);
                                          print_derivation("lvalue", "LOCAL IDENTIFIER");
                                        }
            |   DOUBLE_COLON IDENTIFIER { S_TABLE_SEARCH_GLOBAL_VAR($2,$$,@2);
                                          print_derivation("lvalue", ":: IDENTIFIER");
                                        }
            |   member                  { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                          print_derivation("lvalue", "member");
                                        }
            ;

member      :   lvalue DOT IDENTIFIER                                { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\".\" with");
                                                                       S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                                       print_derivation("member", "lvalue . IDENTIFIER");
                                                                     }
            |   lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET { S_TABLE_CHECK_FUNCTION_ERRORS($1, "\"[]\" with");
                                                                       S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                                       print_derivation("member", "lvalue [ expr ]");
                                                                     }
            |   call DOT IDENTIFIER                                  { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                                       print_derivation("member", "call . IDENTIFIER");
                                                                     }
            |   call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET   { S_TABLE_NO_FURTHER_SYMBOL_CHECK_NEEDED($$);
                                                                       print_derivation("member", "call [ expr ]");
                                                                     }
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

elist       :   %empty         { print_derivation("elist", "empty"); }
            |   expr elist_opt { print_derivation("elist", "expr elist_opt"); }
            ;

elist_opt   :   %empty               { print_derivation("elist_opt", "empty"); }
            |   COMMA expr elist_opt { print_derivation("elist_opt", ", expr elist_opt"); }
            ;

objectdef   :   LEFT_SQUARE_BRACKET elist RIGHT_SQUARE_BRACKET   { print_derivation("objectdef", "[ elist ]"); }
            |   LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET { print_derivation("objectdef", "[ indexed ]"); }
            ;

indexed     :   indexedelem indexed_opt { print_derivation("indexed", "indexedelem indexed_opt"); }
            ;

indexed_opt :   %empty                        { print_derivation("indexed_opt", "empty"); }
            |   COMMA indexedelem indexed_opt { print_derivation("indexed_opt", ", indexedelem indexed_opt"); }
            ;

indexedelem :   LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET { print_derivation("indexedelem", "{ expr : expr }"); }
            ;

block       :   LEFT_CURLY_BRACKET { S_TABLE_BLOCK_ENTER; } block_opt RIGHT_CURLY_BRACKET { S_TABLE_BLOCK_EXIT;
                                                                                            print_derivation("block", "{ block_opt }");
                                                                                          }
            ;

block_opt   :   %empty         { print_derivation("block_opt", "empty"); }
            |   stmt block_opt { print_derivation("block_opt", "stmt block_opt"); }
            ;

funcdef     :   FUNCTION { S_TABLE_FUNC_START_ANONYMOYS(@1); } LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS {S_TABLE_END_LIST_ARG();} block      { S_TABLE_FUNC_END;
                                                                                                                                            print_derivation("funcdef", 
                                                                                                                                            "FUNCTION ( idlist ) block"); 
                                                                                                                                          }
            |   FUNCTION IDENTIFIER { S_TABLE_FUNC_START($2,@2); } LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS {S_TABLE_END_LIST_ARG();} block { S_TABLE_FUNC_END;
                                                                                                                                            print_derivation("funcdef", 
                                                                                                                                            "FUNCTION IDENTIFIER ( idlist ) block");
                                                                                                                                          }
            ;

const       :   INTEGER { print_derivation("const", "INTEGER"); }
            |   FLOAT   { print_derivation("const", "FLOAT"); }
            |   STRING  { print_derivation("const", "STRING"); }
            |   NIL     { print_derivation("const", "NIL"); }
            |   TRUE    { print_derivation("const", "TRUE"); }
            |   FALSE   { print_derivation("const", "FALSE"); }
            ;

idlist      :   %empty                                              { print_derivation("idlist", "empty"); }
            |   IDENTIFIER { S_TABLE_ADD_ARG($1, @1); } idlist_opt { print_derivation("idlist", "IDENTIFIER idlist_opt"); }
            ;

idlist_opt  :   %empty                                               { print_derivation("idlist_opt", "empty"); }
            |   COMMA IDENTIFIER { S_TABLE_ADD_ARG($2,@2); } idlist_opt { print_derivation("idlist_opt", ", IDENTIFIER idlist"); }
            ;

ifstmt      :   IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt %expect 1 { print_derivation("ifstmt", "IF ( expr ) stmt"); }
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
   std::cerr << SET_COLOR_FOR_ERROR << "Error: " << err_message << " at " << l << std::endl << RESET_COLOR;
}
