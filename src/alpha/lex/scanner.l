%{
#include <alpha/lex/scanner.h>

#include <alpha/syntax/parser.h>

#include <alpha/token/token.h>
#include <alpha/lex/status.h>
#include <alpha/lex/error.h>

#include <iostream>
#include <string>
#include <cassert>

#undef  YY_DECL
#define YY_DECL                 int alpha::lex::Scanner::alpha_yylex( \
                                    alpha::syntax::Parser::semantic_type* const lval, \
                                    alpha::syntax::Parser::location_type* location)

#define YY_USER_ACTION          { location->step(); location->columns(yyleng); }
#define UPDATE_LOCATION_LINES   { location->lines(); }

#define SUCCESS                 status::SUCCESS
#define NOT_CLOSED_STRING       status::NOT_CLOSED_STRING
#define NOT_CLOSED_COMMENT      status::NOT_CLOSED_COMMENT
#define UNKNOWN_ESCAPE_CHAR     status::UNKNOWN_ESCAPE_CHAR
#define UNKNOWN_TOKEN           status::UNKNOWN_TOKEN

#define RUNTIME_ASSERT(what)    assert(what)

#define RETURN_TOKEN(CATEGORY) { \
    this->token = Token(yylineno, next_seq_number++, yytext, CATEGORY); \
    this->status = SUCCESS; \
    return CATEGORY; \
}

#define RETURN_CUSTOM_TOKEN(LINENO, VALUE, CATEGORY) { \
    this->token = Token(LINENO, next_seq_number++, VALUE, CATEGORY); \
    this->status = SUCCESS; \
    return CATEGORY; \
}

#define RAISE_ERROR(STATUS) { \
    assert(STATUS != SUCCESS);\
\
    this->status = STATUS; \
    bool should_terminate = this->handle_error(location); \
    if (should_terminate) { \
        yyterminate(); \
    } \
}

using namespace alpha::lex;
using namespace alpha::token;
using category = alpha::token::Token::Category;

static unsigned int next_seq_number = 0;
%}

/* Flex options */
%option noyywrap
%option c++
%option yyclass="alpha::lex::Scanner"
%option yylineno
%option stack

/* Flex macros */
newline         [\n]
delimeter       [ \t]
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

<STRING_S>{newline}     { UPDATE_LOCATION_LINES; 
                          custom.contents += yytext;
                        }
<STRING_S>[^\\\"\n]*    custom.contents += yytext;        /* read until escape char or end of string char */
<STRING_S>\"            { BEGIN(INITIAL);
                          lval->emplace<std::string>(custom.contents);
                          RETURN_CUSTOM_TOKEN(custom.lineno, custom.contents, category::STRING);
                        } /* end of string */
<STRING_S>\\            BEGIN(ESCAPE_S);                  /* escape char follows */
<STRING_S><<EOF>>       RAISE_ERROR(NOT_CLOSED_STRING);
<ESCAPE_S><<EOF>>       RAISE_ERROR(NOT_CLOSED_STRING);
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
<ESCAPE_S>.|"\n"        { RAISE_ERROR(UNKNOWN_ESCAPE_CHAR);
                          BEGIN(STRING_S);
                        }
\"                      { custom.lineno = yylineno;
                          custom.contents = std::string();
                          BEGIN(STRING_S);                /* String literal begins */
                        }

{newline}               UPDATE_LOCATION_LINES;
{whitespaces}           /* ignore whitespaces */
{real}                  lval->emplace<float>(std::stof(yytext)); RETURN_TOKEN(category::FLOAT);
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
{integer}               lval->emplace<int>(std::stoi(yytext)); RETURN_TOKEN(category::INTEGER);

";"                     RETURN_TOKEN(category::SEMICOLON);
","                     RETURN_TOKEN(category::COMMA);
"::"                    RETURN_TOKEN(category::DOUBLE_COLON);
":"                     RETURN_TOKEN(category::COLON);
".."                    RETURN_TOKEN(category::DOUBLE_DOT);
"."                     RETURN_TOKEN(category::DOT);

{identifier}            lval->emplace<std::string>(yytext); RETURN_TOKEN(category::IDENTIFIER);

"//".*                  ;
"/*"                    { this->comment_stack.push(yylineno);
                          yy_push_state(COMMENT_S);
                        }
<COMMENT_S>"/*"         { this->comment_stack.push(yylineno);
                          yy_push_state(COMMENT_S);
                        }
<COMMENT_S>"*/"         { this->comment_stack.pop();
                          yy_pop_state();

                          ;
                        }
<COMMENT_S>.            /* ignore the rest of the characters */
<COMMENT_S>{newline}    UPDATE_LOCATION_LINES;
<COMMENT_S><<EOF>>      RAISE_ERROR(NOT_CLOSED_COMMENT);

<<EOF>>                 RETURN_TOKEN(category::END_OF_FILE);
.                       RAISE_ERROR(UNKNOWN_TOKEN);

%%


bool Scanner::handle_error(alpha::syntax::Parser::location_type* location) {
    bool should_terminate = false;

    std::string message;

    switch (this->status) {
        case SUCCESS:
            assert(0);
            break;
        case NOT_CLOSED_STRING:
            message = "unclossed string";
            should_terminate = true;
            break;
        case NOT_CLOSED_COMMENT:
            message = "unclossed comment";
            should_terminate = true;
            break;
        case UNKNOWN_ESCAPE_CHAR:
            message = "unknown escaped character";
            break;
        case UNKNOWN_TOKEN:
            message = "unknown token `" + std::string(yytext) + "`";
            break;
        default:
            assert(0);
            message = "unknown error";
    };

    error::print(message, *location);

    return should_terminate;
}
