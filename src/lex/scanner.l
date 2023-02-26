%{
#include<assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alpha_token.h>
#include <alpha_token_category.h>
#include <alpha_lex_status.h>
#include "../../include/collections/stack.h"

#define SUCCESS                 ALPHA_LEX_STATUS_SUCCESS
#define NOT_CLOSED_STRING       ALPHA_LEX_STATUS_NOT_CLOSED_STRING
#define NOT_CLOSED_COMMENT      ALPHA_LEX_STATUS_NOT_CLOSED_COMMENT
#define UNKNOWN_ESCAPE_CHAR     ALPHA_LEX_STATUS_UNKNOWN_ESCAPE_CHAR
#define UNKNOWN_TOKEN           ALPHA_LEX_STATUS_UNKNOWN_TOKEN
#define RUNTIME_ASSERT(what)    assert(what)
#define YY_DECL                 int alpha_yylex(void* yylval)

int return_safely(int return_value, stack_t no_of_line_stack);
alpha_token_t add_new_token(alpha_token_t tail, const char* text, alpha_token_category_t category);
void concat_content_of_token(alpha_token_t token, const char* src_content);
char* get_range_as_string(int start, int end);

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
%x STRING
%x ESCAPE

%%
	assert(sizeof(int) == sizeof(yylineno));
	stack_t no_of_line_stack = stack_new(sizeof(int));
	RUNTIME_ASSERT(no_of_line_stack);
	alpha_token_t node = *((alpha_token_t*)yylval);

<STRING>[^\\\"]*	concat_content_of_token(node, yytext); /* read until escape char or end of string char */
<STRING>\"			BEGIN(INITIAL); /* end of string */
<STRING>\\			BEGIN(ESCAPE); /* escape char follows */
<STRING><<EOF>>		return return_safely(NOT_CLOSED_STRING, no_of_line_stack);
<ESCAPE><<EOF>>		return return_safely(NOT_CLOSED_STRING, no_of_line_stack);
<ESCAPE>"\""		{ concat_content_of_token(node, "\"");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>"n"			{ concat_content_of_token(node, "\n");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>"t"			{ concat_content_of_token(node, "\t");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>"\\"		{ concat_content_of_token(node, "\\");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>[.]*		return return_safely(UNKNOWN_ESCAPE_CHAR, no_of_line_stack);
\"					{ node = add_new_token(node, "", ALPHA_TOKEN_STRING);
					  BEGIN(STRING); /* String literal begins */
					}

{whitespaces}		/* ignore whitespaces */
{real}				node = add_new_token(node, yytext, ALPHA_TOKEN_FLOAT);
"="					node = add_new_token(node, yytext, ALPHA_TOKEN_ASSIGN);
"+"					node = add_new_token(node, yytext, ALPHA_TOKEN_PLUS);
"-"					node = add_new_token(node, yytext, ALPHA_TOKEN_MINUS);
"*"					node = add_new_token(node, yytext, ALPHA_TOKEN_STAR);
"/"					node = add_new_token(node, yytext, ALPHA_TOKEN_DIV);
"%"					node = add_new_token(node, yytext, ALPHA_TOKEN_MOD);
"=="				node = add_new_token(node, yytext, ALPHA_TOKEN_EQUALS);
"!="				node = add_new_token(node, yytext, ALPHA_TOKEN_NOT_EQUALS);
"++"				node = add_new_token(node, yytext, ALPHA_TOKEN_PLUS_PLUS);
"--"				node = add_new_token(node, yytext, ALPHA_TOKEN_MINUS_MINUS);
">"					node = add_new_token(node, yytext, ALPHA_TOKEN_GREATER);
"<"					node = add_new_token(node, yytext, ALPHA_TOKEN_LESS);
">="				node = add_new_token(node, yytext, ALPHA_TOKEN_GREATER_EQUALS);
"<="				node = add_new_token(node, yytext, ALPHA_TOKEN_LESS_EQUALS);
"{"					node = add_new_token(node, yytext, ALPHA_TOKEN_LEFT_CURLY_BRACKET);
"}"					node = add_new_token(node, yytext, ALPHA_TOKEN_RIGHT_CURLY_BRACKET);
"["					node = add_new_token(node, yytext, ALPHA_TOKEN_LEFT_SQUARE_BRACKET);
"]"					node = add_new_token(node, yytext, ALPHA_TOKEN_RIGHT_SQUARE_BRACKET);
"("					node = add_new_token(node, yytext, ALPHA_TOKEN_LEFT_PARENTHESIS);
")"					node = add_new_token(node, yytext, ALPHA_TOKEN_RIGHT_PARENTHESIS);

"if"				node = add_new_token(node, yytext, ALPHA_TOKEN_IF);
"else"				node = add_new_token(node, yytext, ALPHA_TOKEN_ELSE);
"while"				node = add_new_token(node, yytext, ALPHA_TOKEN_WHILE);
"for"				node = add_new_token(node, yytext, ALPHA_TOKEN_FOR);
"function"			node = add_new_token(node, yytext, ALPHA_TOKEN_FUNCTION);
"return"			node = add_new_token(node, yytext, ALPHA_TOKEN_RETURN);
"break"				node = add_new_token(node, yytext, ALPHA_TOKEN_BREAK);
"continue"			node = add_new_token(node, yytext, ALPHA_TOKEN_CONTINUE);
"and"				node = add_new_token(node, yytext, ALPHA_TOKEN_AND);
"not"				node = add_new_token(node, yytext, ALPHA_TOKEN_NOT);
"or"				node = add_new_token(node, yytext, ALPHA_TOKEN_OR);
"local"				node = add_new_token(node, yytext, ALPHA_TOKEN_LOCAL);
"true"				node = add_new_token(node, yytext, ALPHA_TOKEN_TRUE);
"false"				node = add_new_token(node, yytext, ALPHA_TOKEN_FALSE);
"nil"				node = add_new_token(node, yytext, ALPHA_TOKEN_NIL);
{integer} 			node = add_new_token(node, yytext, ALPHA_TOKEN_INTEGER);

";"					node = add_new_token(node, yytext, ALPHA_TOKEN_SEMICOLON);
","					node = add_new_token(node, yytext, ALPHA_TOKEN_COMMA);
"::"				node = add_new_token(node, yytext, ALPHA_TOKEN_DOUBLE_COLON);
":"					node = add_new_token(node, yytext, ALPHA_TOKEN_COLON);
".."				node = add_new_token(node, yytext, ALPHA_TOKEN_DOUBLE_DOT);
"."					node = add_new_token(node, yytext, ALPHA_TOKEN_DOT);

{identifier}		node = add_new_token(node, yytext, ALPHA_TOKEN_IDENTIFIER);

"//".*				node = add_new_token(node, "", ALPHA_TOKEN_ONE_LINE_COMMENT);
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
					  node = add_new_token(node, line_range, ALPHA_TOKEN_BLOCK_COMMENT);
					  free(line_range);
					  line_range = NULL;

					  yy_pop_state();
					}
<COMMENT>.|"\n"		/* ignore the rest of the characters */
<COMMENT><<EOF>>	return return_safely(NOT_CLOSED_COMMENT, no_of_line_stack);

<<EOF>>				return return_safely(SUCCESS, no_of_line_stack);
.					return return_safely(UNKNOWN_TOKEN, no_of_line_stack);

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

/**
 * @brief Dynamically concatenates 2 strings
 *
 * @param left The left part of the concatenated string
 * @param right The right part of the concatenated string
 * @return null if concatenation failed, else the concatenated string
 *
 * @pre @p left != null
 * @pre @p right != null
 *
 * @post @p left and @p right will be left intact
 * @post Memory for the concatenated string will be allocated using `malloc`
 * (user should call `free` to free the memory)
 *
 */
char* strcat_dynamic(const char* left, const char* right) {
  assert(left);
  assert(right);

  char* concatenated_str =
      malloc(sizeof(char) * (strlen(left) + strlen(right) + 1));

  if (!concatenated_str) {
    return NULL;
  }

  concatenated_str = strcpy(concatenated_str, left);
  concatenated_str = strcat(concatenated_str, right);

  assert(concatenated_str);
  assert(!strncmp(concatenated_str, left, strlen(left)));
  assert(
      !strncmp(&concatenated_str[strlen(left)], right, strlen(right)));
  return concatenated_str;
}

void concat_content_of_token(alpha_token_t token, const char* src_content) {
	assert(token);
	assert(src_content);

	const char* token_content = alpha_token_getContent(token);
	char* temp_str = strcat_dynamic(token_content, src_content);
	RUNTIME_ASSERT(temp_str);

	int ok = alpha_token_setContent(token, temp_str);
	RUNTIME_ASSERT(ok);
	token_content = NULL; // token_content is not valid anymore

	free(temp_str);
	temp_str = NULL;
}

alpha_token_t add_new_token(alpha_token_t tail, const char* text, alpha_token_category_t category) {
	int next_sequence_number = alpha_token_getSequenceNumber(tail) + 1;

	alpha_token_t new_token = alpha_token_new(yylineno, next_sequence_number, text, category);
	RUNTIME_ASSERT(new_token);

	int result = alpha_token_setNext(tail, new_token);
	RUNTIME_ASSERT(result);

	return new_token;
}
