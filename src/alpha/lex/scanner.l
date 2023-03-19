%{
#include <alpha/lex/scanner.h>

#include <alpha/token/token.h>
#include <alpha/token/category.h>
#include <alpha/lex/status.h>

#include <iostream>
#include <string>

#undef  YY_DECL
#define YY_DECL                 int alpha::lex::Scanner::yylex(alpha::token::Token& token)

#define SUCCESS                 status::SUCCESS
#define NOT_CLOSED_STRING       status::NOT_CLOSED_STRING
#define NOT_CLOSED_COMMENT      status::NOT_CLOSED_COMMENT
#define UNKNOWN_ESCAPE_CHAR     status::UNKNOWN_ESCAPE_CHAR
#define UNKNOWN_TOKEN           status::UNKNOWN_TOKEN
#define END_OF_FILE             status::END_OF_FILE

#define RUNTIME_ASSERT(what)    assert(what)

#define RETURN_TOKEN(CATEGORY)                          token = Token(yylineno, next_seq_number++, yytext, CATEGORY); return SUCCESS;
#define RETURN_CUSTOM_TOKEN(LINENO, VALUE, CATEGORY)    token = Token(LINENO, next_seq_number++, VALUE, CATEGORY); return SUCCESS;

using namespace alpha::lex;
using namespace alpha::token;

static unsigned int next_seq_number = 0;
%}

/* Flex options */
%option noyywrap
%option c++
%option yyclass="alpha::lex::Scanner"
%option yylineno
%option stack

/* Flex macros */
delimeter       [ \t\n]
whitespaces     {delimeter}+
letter          [a-zA-Z]
digit           [0-9]
underscore      [_]
identifier      {letter}({letter}|{digit}|{underscore})*
integer         {digit}+
real            {integer}\.{integer}

%x COMMENT_S
%x STRING_S
%x ESCAPE_S

%%
                        struct {
                            std::string contents;
                           unsigned int lineno;
                        } custom = {"default", 0};

<STRING_S>[^\\\"]*      custom.contents += yytext;      /* read until escape char or end of string char */
<STRING_S>\"            RETURN_CUSTOM_TOKEN(custom.lineno, custom.contents, category::STRING);       /* end of string */
<STRING_S>\\            BEGIN(ESCAPE_S);                  /* escape char follows */
<STRING_S><<EOF>>       return NOT_CLOSED_STRING;
<ESCAPE_S><<EOF>>       return NOT_CLOSED_STRING;
<ESCAPE_S>"\""          { custom.contents += "\"";
                          BEGIN(STRING_S);                /* which escaped char? */
                        }
<ESCAPE_S>"n"           { custom.contents += "\n";
                          BEGIN(STRING_S);                /* which escaped char? */
                        }
<ESCAPE_S>"t"           { custom.contents += "\t";
                          BEGIN(STRING_S);                /* which escaped char? */
                        }
<ESCAPE_S>"\\"          { custom.contents += "\\";
                          BEGIN(STRING_S);                /* which escaped char? */
                        }
<ESCAPE_S>.|"\n"        return UNKNOWN_ESCAPE_CHAR;
\"                      { custom.lineno = yylineno;
                          BEGIN(STRING_S);                /* String literal begins */
                        }

{whitespaces}           /* ignore whitespaces */
{real}                  RETURN_TOKEN(category::FLOAT)
"="                     RETURN_TOKEN(category::ASSIGN)
"+"                     RETURN_TOKEN(category::PLUS)
"-"                     RETURN_TOKEN(category::MINUS)
"*"                     RETURN_TOKEN(category::STAR);
"/"                     RETURN_TOKEN(category::DIV);
"%"                     RETURN_TOKEN(category::MOD);
"=="                    RETURN_TOKEN(category::EQUALS);
"!="                    RETURN_TOKEN(category::NOT_EQUALS);
"++"                    RETURN_TOKEN(category::PLUS_PLUS);
"--"                    RETURN_TOKEN(category::MINUS_MINUS);
">"                     RETURN_TOKEN(category::GREATER);
"<"                     RETURN_TOKEN(category::LESS);
">="                    RETURN_TOKEN(category::GREATER_EQUALS);
"<="                    RETURN_TOKEN(category::LESS_EQUALS);
"{"                     RETURN_TOKEN(category::LEFT_CURLY_BRACKET);
"}"                     RETURN_TOKEN(category::RIGHT_CURLY_BRACKET);
"["                     RETURN_TOKEN(category::LEFT_SQUARE_BRACKET);
"]"                     RETURN_TOKEN(category::RIGHT_SQUARE_BRACKET);
"("                     RETURN_TOKEN(category::LEFT_PARENTHESIS);
")"                     RETURN_TOKEN(category::RIGHT_PARENTHESIS);

"if"                    RETURN_TOKEN(category::IF);
"else"                  RETURN_TOKEN(category::ELSE);
"while"                 RETURN_TOKEN(category::WHILE);
"for"                   RETURN_TOKEN(category::FOR);
"function"              RETURN_TOKEN(category::FUNCTION);
"return"                RETURN_TOKEN(category::RETURN);
"break"                 RETURN_TOKEN(category::BREAK);
"continue"              RETURN_TOKEN(category::CONTINUE);
"and"                   RETURN_TOKEN(category::AND);
"not"                   RETURN_TOKEN(category::NOT);
"or"                    RETURN_TOKEN(category::OR);
"local"                 RETURN_TOKEN(category::LOCAL);
"true"                  RETURN_TOKEN(category::TRUE);
"false"                 RETURN_TOKEN(category::FALSE);
"nil"                   RETURN_TOKEN(category::NIL);
{integer}               RETURN_TOKEN(category::INTEGER);

";"                     RETURN_TOKEN(category::SEMICOLON);
","                     RETURN_TOKEN(category::COMMA);
"::"                    RETURN_TOKEN(category::DOUBLE_COLON);
":"                     RETURN_TOKEN(category::COLON);
".."                    RETURN_TOKEN(category::DOUBLE_DOT);
"."                     RETURN_TOKEN(category::DOT);

{identifier}            RETURN_TOKEN(category::IDENTIFIER);

"//".*                  RETURN_CUSTOM_TOKEN(yylineno, "", category::ONE_LINE_COMMENT);
"/*"                    { this->comment_stack.push(yylineno);
                          yy_push_state(COMMENT_S);
                        }
<COMMENT_S>"/*"         { this->comment_stack.push(yylineno);
                          yy_push_state(COMMENT_S);
                        }
<COMMENT_S>"*/"         { custom.lineno =  this->comment_stack.top();
                          this->comment_stack.pop();
                          custom.contents = std::to_string(custom.lineno) + "-" + std::to_string(yylineno);

                          yy_pop_state();

                          RETURN_CUSTOM_TOKEN(custom.lineno, custom.contents, category::BLOCK_COMMENT);
                        }
<COMMENT_S>.|"\n"       /* ignore the rest of the characters */
<COMMENT_S><<EOF>>      return NOT_CLOSED_COMMENT;

<<EOF>>                 return END_OF_FILE;
.                       return UNKNOWN_TOKEN;

%%

