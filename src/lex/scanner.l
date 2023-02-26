%{
#include<assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alpha_token.h>
#include <alpha_token_category.h>
#include "../../include/collections/stack.h"

#define SUCCESS 0
#define NOT_CLOSED_STRING 	-1
#define NOT_CLOSED_COMMENT	-2
#define RUNTIME_ASSERT(what) assert(what)
#define YY_DECL int alpha_yylex(void* yylval)
%}

/* Flex options */
%option outfile="../src/lex/scanner.c"
%option header-file="../include/lex/scanner.h"
%option noyywrap
%option yylineno
%option stack

/* Flex macros */
delimeter	[ \t\n]
whitespaces	{delimeter}+
letter		[a-zA-Z]
digit		[0-9]
underscore	[_]
identifier	{letter}({letter}|{digit}|{underscore})*
/* Changed from "number" to "integer" */
integer		{digit}+
/* Nick's additions */
real		{integer}\.{integer}

%x COMMENT
%s STRING
%s ESCAPE

%%
stack_t no_of_line_stack = stack_new(sizeof(int));
RUNTIME_ASSERT(no_of_line_stack);


<STRING>[^\\\"]*	/* read until escape char or end of string char */
<STRING>\"			BEGIN(INITIAL); /* end of string */
<STRING>\\			BEGIN(ESCAPE); /* escape char follows */
<STRING><<EOF>>		return return_safely(NOT_CLOSED_STRING, no_of_line_stack);
<ESCAPE>[\"nt\\]	BEGIN(STRING); /* which escaped char? */
<ESCAPE>[.]*		/* Unknown escaped charachter (No mans land) */
<ESCAPE><<EOF>>		return return_safely(NOT_CLOSED_STRING, no_of_line_stack);
\"					BEGIN(STRING); /* String literal begins */

{whitespaces}		/* ignore whitespaces */
{real}				yylval = new_token(yylval, yytext, ALPHA_TOKEN_FLOAT);
"="					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_ASSIGN);
"+"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_PLUS);
"-"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_MINUS);
"*"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_STAR);
"/"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_DIV);
"%"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_MOD);
"=="				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_EQUALS);
"!="				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_NOT_EQUALS);
"++"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_PLUS_PLUS);
"--"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_MINUS_MINUS);
">"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_GREATER);
"<"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_LESS);
">="				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_GREATER_EQUALS);
"<="				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_LESS_EQUALS);
"{"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_LEFT_CURLY_BRACKET);
"}"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_RIGHT_CURLY_BRACKET);
"["					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_LEFT_SQUARE_BRACKET);
"]"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_RIGHT_SQUARE_BRACKET);
"("					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_LEFT_PARENTHESIS);
")"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_RIGHT_PARENTHESIS);

"if"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_IF);
"else"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_ELSE);
"while"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_WHILE);
"for"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_FOR);
"function"			yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_FUNCTION);
"return"			yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_RETURN);
"break"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_BREAK);
"continue"			yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_CONTINUE);
"and"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_AND);
"not"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_NOT);
"or"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_OR);
"local"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_LOCAL);
"true"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_TRUE);
"false"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_FALSE);
"nil"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_NIL);
{integer} 			yylval = new_token(yylval, yytext, ALPHA_TOKEN_INTEGER);

";"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_SEMICOLON);
","					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_COMMA);
"::"				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_DOUBLE_COLON);
":"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_COLON);
".."				yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_DOUBLE_DOT);
"."					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_DOT);

{identifier}		yylval = new_token(yylval, yytext, ALPHA_TOKEN_IDENTIFIER);

"//".*				yylval = new_token(yylval, "", ALPHA_TOKEN_ONE_LINE_COMMENT);
"/*"				{ int result = stack_push(no_of_line_stack, &yylineno);
					  RUNTIME_ASSERT(result);
					  yy_push_state(COMMENT);
					}
<COMMENT>"/*"		{ int result = stack_push(no_of_line_stack, &yylineno);
					  RUNTIME_ASSERT(result);
					  yy_push_state(COMMENT);
					}
<COMMENT>"*/"		{ int start_of_comment;
					  stack_pop(no_of_line_stack, &start_of_comment);

					  char* line_range = get_range_as_string(start_of_comment, yylineno);
					  yylval = add_new_token(yylval, line_range, ALPHA_TOKEN_BLOCK_COMMENT);
					  free(line_range);
					  line_range = NULL;

					  yy_pop_state();
					}
<COMMENT>.			/* ignore the rest of the characters */
<COMMENT><<EOF>>	return return_safely(NOT_CLOSED_COMMENT, no_of_line_stack);

<<EOF>>				return return_safely(SUCCESS, no_of_line_stack);
.					{fprintf(stderr, "Cannot match character '%s' with any rule\n", yytext);}

%%

int return_safely(int return_value, stack_t no_of_line_stack) {
	stack_free(no_of_line_stack);
	return return_value;
}

int get_number_of_digits(int x) {
  int no_of_digits = 0;

  do {
    x /= 10;
    no_of_digits++;
  } while (x != 0);

  return no_of_digits;
}

char* get_range_as_string(int start, int end) {
  assert(start <= end);

  int digits_of_start = get_number_of_digits(start);
  int digits_of_end = get_number_of_digits(end);

  char* range = malloc(sizeof(char) * (digits_of_start + digits_of_end + 2));
  RUNTIME_ASSERT(range);
  char* start_as_string = malloc(sizeof(char) * (digits_of_start + 1));
  RUNTIME_ASSERT(start_as_string);
  char* end_as_string = malloc(sizeof(char) * (digits_of_end + 1));
  RUNTIME_ASSERT(end_as_string);

  sprintf(start_as_string, "%d", start);
  sprintf(end_as_string, "%d", end);

  range = strcpy(range, start_as_string);
  range = strcat(range, "-");
  range = strcat(range, end_as_string);

  free(start_as_string);
  start_as_string = NULL;
  free(end_as_string);
  end_as_string = NULL;

  return range;
}

alpha_token_t add_new_token(alpha_token_t tail, const char* text, alpha_token_category_t category) {
	int next_sequence_number = alpha_token_getSequenceNumber(tail) + 1;

	alpha_token_t new_token = alpha_token_new(yylineno, next_sequence_number, text, category);
	RUNTIME_ASSERT(new_token);

	int result = alpha_token_setNext(tail, new_token);
	RUNTIME_ASSERT(result);

	return new_token;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    if (!(yyin = fopen(argv[1], "r"))) {
      fprintf(stderr, "Cannot read file: %s\n", argv[1]);
      return 1;
    }
  } else {
    yyin = stdin;
  }

  alpha_token_t head = alpha_token_new(0,0,"",0);
  alpha_yylex(head);

  alpha_token_t temp = head;
  head = alpha_token_getNext(head);
  alpha_token_free(temp);

  return 0;
}
