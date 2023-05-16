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

    #include <alpha/syntax/manager/nonterminal.h>
    #include <alpha/syntax/manager/terminal.h>

    namespace nterm = alpha::syntax::manager::nonterminal;
    namespace terminal = alpha::syntax::manager::terminal;
}

%parse-param { alpha::lex::Scanner &scanner }
%parse-param { alpha::symbol::Table &symbol_table }

%locations
%define api.location.include {<alpha/syntax/location.h>}

%define parse.error verbose

%code {
    #include <iostream>
    #include <cassert>

    #include <alpha/lex/scanner.h>
    #include <alpha/symbol/table.h>
    #include <alpha/syntax/error.h>

    #undef yylex
    #define yylex scanner.alpha_yylex

    static void print_derivation(const std::string&, const std::string&);
}

/* The grammar expects 1 shift/reduce conflict (ifstmt) */
%expect 1

/* For token types */
%define api.value.type variant

%token END_OF_FILE 0 "end of file"
%token <int> INTEGER
%token <double> FLOAT
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
%token ASSIGN               "="
%token PLUS                 "+"
%token MINUS                "-"
%token STAR                 "*"
%token DIV                  "/"
%token MOD                  "%"
%token EQUALS               "=="
%token NOT_EQUALS           "!="
%token PLUS_PLUS            "++"
%token MINUS_MINUS          "--"
%token GREATER              ">"
%token LESS                 "<"
%token GREATER_EQUALS       ">="
%token LESS_EQUALS          "<="
%token LEFT_CURLY_BRACKET   "{"
%token RIGHT_CURLY_BRACKET  "}"
%token LEFT_SQUARE_BRACKET  "["
%token RIGHT_SQUARE_BRACKET "]"
%token LEFT_PARENTHESIS     "("
%token RIGHT_PARENTHESIS    ")"
%token SEMICOLON            ";"
%token COMMA                ","
%token COLON                ":"
%token DOUBLE_COLON         "::"
%token DOT                  "."
%token DOUBLE_DOT           ".."

%type <nterm::Assignexpr>  assignexpr
%type <nterm::BlockClose>  block_close
%type <nterm::BlockOpen>   block_open
%type <nterm::Expr>        expr
%type <nterm::Funcdef>     funcdef
%type <nterm::Funcprefix>  funcprefix
%type <nterm::Lvalue>      lvalue
%type <nterm::Member>      member
%type <nterm::Primary>     primary
%type <nterm::Term>        term

%start PROGRAM

%right      "="
%left       OR
%left       AND
%nonassoc   "=="    "!="
%nonassoc   ">"     ">="    "<"     "<="
%left       "+"     "-"
%left       "*"     "/"     "%"
%right      NOT     "++"    "--"    UMINUS
%left       "."     ".."
%left       "["     "]"
%left       "("     ")"

%%

PROGRAM     :   %empty       { print_derivation("PROGRAM", "empty"); }
            |   stmt PROGRAM { print_derivation("PROGRAM", "stmt PROGRAM"); }
            ;

stmt        :   expr ";"     { print_derivation("stmt", "expr ;"); }
            |   ifstmt       { print_derivation("stmt", "ifstmt"); }
            |   whilestmt    { print_derivation("stmt", "whilestmt"); }
            |   forstmt      { print_derivation("stmt", "forstmt"); }
            |   returnstmt   { print_derivation("stmt", "returnstmt"); }
            |   breakstmt    { print_derivation("stmt", "breakstmt"); }
            |   continuestmt { print_derivation("stmt", "continuestmt"); }
            |   block        { print_derivation("stmt", "block"); }
            |   funcdef      { print_derivation("stmt", "funcdef"); }
            |   ";"          { print_derivation("stmt", ";"); }
            ;

expr        :   assignexpr     { $$ = nterm::Expr::from_assignexpr();
                                 print_derivation("expr", "assignexpr");
                               }
            |   expr "+" expr  { $$ = nterm::Expr::from_expr_plusTkn_expr($1, $3);
                                 print_derivation("expr", "expr + expr");
                               }
            |   expr "-" expr  { $$ = nterm::Expr::from_expr_minusTkn_expr($1, $3);
                                 print_derivation("expr", "expr - expr");
                               }
            |   expr "*" expr  { $$ = nterm::Expr::from_expr_starTkn_expr($1, $3);
                                 print_derivation("expr", "expr * expr");
                               }
            |   expr "/" expr  { $$ = nterm::Expr::from_expr_divTkn_expr($1, $3);
                                 print_derivation("expr", "expr / expr");
                               }
            |   expr "%" expr  { $$ = nterm::Expr::from_expr_modTkn_expr($1, $3);
                                 print_derivation("expr", "expr % expr");
                               }
            |   expr ">" expr  { $$ = nterm::Expr::from_expr_greaterTkn_expr($1, $3);
                                 print_derivation("expr", "expr > expr");
                               }
            |   expr ">=" expr { $$ = nterm::Expr::from_expr_greaterEqTkn_expr($1, $3);
                                 print_derivation("expr", "expr >= expr");
                               }
            |   expr "<" expr  { $$ = nterm::Expr::from_expr_lessTkn_expr($1, $3);
                                 print_derivation("expr", "expr < expr");
                               }
            |   expr "<=" expr { $$ = nterm::Expr::from_expr_lessEqTkn_expr($1, $3);
                                 print_derivation("expr", "expr <= expr");
                               }
            |   expr "==" expr { $$ = nterm::Expr::from_expr_equalsTkn_expr($1, $3);
                                 print_derivation("expr", "expr == expr");
                               }
            |   expr "!=" expr { $$ = nterm::Expr::from_expr_notEqualsTkn_expr($1, $3);
                                 print_derivation("expr", "expr != expr");
                               }
            |   expr AND expr  { $$ = nterm::Expr::from_expr_andTkn_expr($1, $3);
                                 print_derivation("expr", "expr AND expr");
                               }
            |   expr OR expr   { $$ = nterm::Expr::from_expr_orTkn_expr($1, $3);
                                 print_derivation("expr", "expr OR expr");
                               }
            |   term           { $$ = nterm::Expr::from_term($1);
                                 print_derivation("expr", "term");
                               }
            ;

term        :   "(" expr ")"          { $$ = nterm::Term::from_lParTkn_expr_rParTkn($2);
                                        print_derivation("term", "( expr )");
                                      }
            |   "-" expr %prec UMINUS { $$ = nterm::Term::from_minusTkn_expr($2);
                                        print_derivation("term", "- expr");
                                      }
            |   NOT expr              { $$ = nterm::Term::from_notTkn_expr($2);
                                        print_derivation("term", "NOT expr");
                                      }
            |   "++" lvalue           { $$ = nterm::Term::from_plusPlusTkn_lvalue($2);
                                        print_derivation("term", "++ lvalue");
                                      }
            |   lvalue "++"           { $$ = nterm::Term::from_lvalue_plusPlusTkn($1);
                                        print_derivation("term", "lvalue ++");
                                      }
            |   "--" lvalue           { $$ = nterm::Term::from_minusMinusTkn_lvalue($2);
                                        print_derivation("term", "-- lvalue");
                                      }
            |   lvalue "--"           { $$ = nterm::Term::from_lvalue_minusMinusTkn($1);
                                        print_derivation("term", "lvalue --");
                                      }
            |   primary               { $$ = nterm::Term::from_primary($1);
                                        print_derivation("term", "primary");
                                      }
            ;

assignexpr  :   lvalue "=" expr { $$ = nterm::Assignexpr::from_lvalue_assignTkn_expr($1);
                                  print_derivation("assignexpr", "lvalue = expr");
                                }
            ;

primary     :   lvalue          { $$ = nterm::Primary::from_lvalue($1);
                                  print_derivation("primary", "lvalue");
                                }
            |   call            { $$ = nterm::Primary::from_call();
                                  print_derivation("primary", "call");
                                }
            |   objectdef       { $$ = nterm::Primary::from_objectdef();
                                  print_derivation("primary", "objectdef");
                                }
            |   "(" funcdef ")" { $$ = nterm::Primary::from_lParTkn_funcdef_rParTkn($2);
                                  print_derivation("primary", "( funcdef )");
                                }
            |   const           { $$ = nterm::Primary::from_const();
                                  print_derivation("primary", "const");
                                }
            ;

lvalue      :   IDENTIFIER       { $$ = nterm::Lvalue::from_idTkn(terminal::Identifier($1, @1));
                                   print_derivation("lvalue", "IDENTIFIER"); 
                                 }
            |   LOCAL IDENTIFIER { $$ = nterm::Lvalue::from_localIdTkn(terminal::Identifier($2, @2));
                                   print_derivation("lvalue", "LOCAL IDENTIFIER");
                                 }
            |   "::" IDENTIFIER  { $$ = nterm::Lvalue::from_doubleColonTkn_localIdTkn(terminal::Identifier($2, @2));
                                   print_derivation("lvalue", ":: IDENTIFIER");
                                 }
            |   member           { $$ = nterm::Lvalue::from_member();
                                   print_derivation("lvalue", "member");
                                 }
            ;

member      :   lvalue "." IDENTIFIER { $$ = nterm::Member::from_lvalue_dotTkn_idTkn($1);
                                        print_derivation("member", "lvalue . IDENTIFIER");
                                      }
            |   lvalue "[" expr "]"   { $$ = nterm::Member::from_lvalue_lSqrBrackTkn_expr_rSqrtBrackTkn($1);
                                        print_derivation("member", "lvalue [ expr ]");
                                      }
            |   call "." IDENTIFIER   { $$ = nterm::Member::from_call_dotTkn_idTkn();
                                        print_derivation("member", "call . IDENTIFIER");
                                      }
            |   call "[" expr "]"     { $$ = nterm::Member::from_call_lSqrBrackTkn_expr_rSqrtBrackTkn();
                                        print_derivation("member", "call [ expr ]");
                                      }
            ;

call        :   call "(" elist ")"            { print_derivation("call", "call ( elist )"); }
            |   lvalue  callsuffix            { print_derivation("call", "lvalue callsuffix"); }
            |   "(" funcdef ")" "(" elist ")" { print_derivation("call", "( funcdef ) ( elist )"); }
            ;

callsuffix  :   normcall   { print_derivation("callsuffix", "normcall"); }
            |   methodcall { print_derivation("callsuffix", "methodcall"); }
            ;

normcall    :   "(" elist ")" { print_derivation("normcall", "( elist )"); }
            ;

methodcall  :   ".." IDENTIFIER "(" elist ")" { print_derivation("methodcall", ".. IDENTIFIER ( elist )"); }
            ;

elist       :   %empty         { print_derivation("elist", "empty"); }
            |   expr elist_opt { print_derivation("elist", "expr elist_opt"); }
            ;

elist_opt   :   %empty             { print_derivation("elist_opt", "empty"); }
            |   "," expr elist_opt { print_derivation("elist_opt", ", expr elist_opt"); }
            ;

objectdef   :   "[" elist "]"   { print_derivation("objectdef", "[ elist ]"); }
            |   "[" indexed "]" { print_derivation("objectdef", "[ indexed ]"); }
            ;

indexed     :   indexedelem indexed_opt { print_derivation("indexed", "indexedelem indexed_opt"); }
            ;

indexed_opt :   %empty                      { print_derivation("indexed_opt", "empty"); }
            |   "," indexedelem indexed_opt { print_derivation("indexed_opt", ", indexedelem indexed_opt"); }
            ;

indexedelem :   "{" expr ":" expr "}" { print_derivation("indexedelem", "{ expr : expr }"); }
            ;

block       :   block_open block_body block_close { print_derivation("block", "block_open block_body block_close"); }

block_open  :   "{" { nterm::BlockOpen::leftCurlyBracketTkn();
                      print_derivation("block_open", "{");
                    }
            ;

block_body  :   %empty { print_derivation("block_body", "empty"); }
            |   stmts  { print_derivation("block_body", "stmts"); }
            ;

stmts       :   stmt       { print_derivation("stmts", "stmt"); }
            |   stmts stmt { print_derivation("stmts", "stmts stmt"); }
            ;

block_close :   "}" { nterm::BlockClose::rightCurlyBracketTkn();
                      print_derivation("block_close", "}");
                    }
            ;

funcdef     :   funcprefix funcargs funcbody { $$ = nterm::Funcdef::from_funcprefix_funcargs_funcbody($1);
                                               print_derivation("funcdef", "funcprefix funcargs funcbody");
                                             }
            ;

funcprefix  :   FUNCTION            { $$ = nterm::Funcprefix::from_functionTkn(terminal::Function(@1));
                                      print_derivation("funcprefix", "FUNCTION");
                                    }
            |   FUNCTION IDENTIFIER { $$ = nterm::Funcprefix::from_functionTkn_identifierTkn(terminal::Identifier($2, @2));
                                      print_derivation("funcprefix", "FUNCTION IDENTIFIER");
                                    }
            ;

funcargs    :   "(" idlist ")" { nterm::Funcargs::lParTkn_idlist_rParTkn();
                                 print_derivation("funcargs", "( idlist )");
                               }
            ;

funcbody    :   funcbody_pre block funcbody_post { nterm::Funcbody::block();
                                                   print_derivation("funcbody", "funcbody_pre block funcbody_post");
                                                 }
            ;

funcbody_pre:   %empty { print_derivation("funcbody_pre", "empty"); }
            ;

funcbody_post   :   %empty { print_derivation("funcbody_post", "empty"); }
                ;


const       :   INTEGER { print_derivation("const", "INTEGER"); }
            |   FLOAT   { print_derivation("const", "FLOAT"); }
            |   STRING  { print_derivation("const", "STRING"); }
            |   NIL     { print_derivation("const", "NIL"); }
            |   TRUE    { print_derivation("const", "TRUE"); }
            |   FALSE   { print_derivation("const", "FALSE"); }
            ;

idlist      :   %empty               { print_derivation("idlist", "empty"); }
            |   idlist_id idlist_opt { print_derivation("idlist", "idlist_id idlist_opt"); }
            ;

idlist_id   :   IDENTIFIER { nterm::IdlistId::identifierTkn(terminal::Identifier($1, @1));
                             print_derivation("idlist_id", "IDENTIFIER");
                           }
            ;

idlist_opt  :   %empty                   { print_derivation("idlist_opt", "empty"); }
            |   idlist_id "," idlist_opt { print_derivation("idlist_opt", "idlist_id , idlist_opt"); }
            ;

ifstmt      :   ifstmt_if stmt        %expect 1 { print_derivation("ifstmt", "ifstmt_if stmt"); }
            |   ifstmt_if stmt ifstmt_else stmt { print_derivation("ifstmt", "ifstmt_if stmt ifstmt_else stmt"); }
            ;

ifstmt_if   :   IF "(" expr ")" { print_derivation("ifstmt_if", "IF ( expr )"); }
            ;

ifstmt_else :   ELSE { $$ = nterm::IfstmtElse::from_elseTkn($1);
                       print_derivation("ifstmt_else", "ELSE");
                     }
            ;


whilestmt       :   whilestmt_while whilestmt_cond loop_stmt { print_derivation("whilestmt", "whilestmt_while whilestmt_cond loop_stmt"); }
                ;

whilestmt_while :   WHILE { print_derivation("whilestmt_while", "WHILE"); }
                ;

whilestmt_cond  :   "(" expr ")" { print_derivation("whilestmt_cond", "( expr )"); }
                ;

forstmt     :   forstmt_pre forstmt_n elist ")" forstmt_n loop_stmt forstmt_n { print_derivation("forstmt", "forstmt_pre forstmt_n elist ) forstmt_n loop_stmt forstmt_n"); }
            ;

forstmt_pre :   FOR "(" elist ";" forstmt_m expr ";" { print_derivation("forstmt_pre", "FOR ( elist ; forstmt_m expr ;"); }
            ;

forstmt_n   :   %empty { print_derivation("forstmt_n", "empty"); }
            ;

forstmt_m   :   %empty { print_derivation("forstmt_n", "empty"); }
            ;

loop_stmt   :   loop_start stmt loop_end { print_derivation("loop_stmt", "loopstart stmt loopend"); }
            ;

loop_start  :   %empty { print_derivation("loop_start", "empty"); }
            ;

loop_end    :   %empty { print_derivation("loop_end", "empty"); }
            ;

breakstmt   :   BREAK ";" { print_derivation("breakstmt", "BREAK ;"); }
            ;

continuestmt:   CONTINUE ";" { print_derivation("breakstmt", "CONTINUE ;"); }
            ;

returnstmt  :   RETURN ";"      { print_derivation("returnstmt", "RETURN ;"); }
            |   RETURN expr ";" { print_derivation("returnstmt", "RETURN expr ;"); }
            ;

%%

static void print_derivation(const std::string& non_final, const std::string& final) {
    std::cout << non_final << "\t\t -> \t" << final << std::endl;
}

void alpha::syntax::Parser::error(const location_type &l, const std::string &err_message) {
   error::print(err_message, l);
}
