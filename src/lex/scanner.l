%{
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include "../../include/token/alpha_token.h"
#include "../../include/token/alpha_token_category.h"

#define NOT_CLOSED_STRING 	-1
#define NOT_CLOSED_COMMENT	-2
#define RUNTIME_ASSERT(what) assert(what)
#define YY_DECL int alpha_yylex(void* yylval)
%}

/* Flex options */
%option noyywrap
%option yylineno

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

%x COMMENT INCLUDE
%s STRING
%s ESCAPE

%%

<STRING>[^\\\"]*	concat_content_of_token(yylval, yytext); /* read until escape char or end of string char */
<STRING>\"			BEGIN(INITIAL); /* end of string */
<STRING>\\			BEGIN(ESCAPE); /* escape char follows */
<STRING><<EOF>>		return NOT_CLOSED_STRING;
<ESCAPE>"\""		{ concat_content_of_token(yylval, "\"");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>"n"			{ concat_content_of_token(yylval, "\n");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>"t"			{ concat_content_of_token(yylval, "\t");
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>"\\"		{ concat_content_of_token(yylval, "\\")
					  BEGIN(STRING); /* which escaped char? */
					}
<ESCAPE>[.]*		{ char* temp_str = strcat_dynamic("/", yytext);
					  concat_content_of_token(yylval, temp_str);
					  free(temp_str);
					}
<ESCAPE><<EOF>>		return NOT_CLOSED_STRING;
\"					{ yylval = new_token(yylval, "", ALPHA_TOKEN_STRING);
					  BEGIN(STRING); /* String literal begins */
					}

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

"//".*				{fprintf(stderr, "Recognized oneline comment with content: %s\n", yytext);}
"/*"				{fprintf(stderr, "Recognized multiline comment with with line range: %d-", yylineno);
					 BEGIN(COMMENT);
					}
<COMMENT>[^*]*		/* eat anything that's not a '*' = do nothing */
<COMMENT>"*"+[^*/]*	/* eat anything that's not a '*' = do nothing */
<COMMENT>"*"+"/"*	{fprintf(stderr, "%d\n", yylineno);
					 BEGIN(INITIAL);
					}
<COMMENT><<EOF>>	return NOT_CLOSED_COMMENT;
.					{fprintf(stderr, "Cannot match character '%s' with any rule\n", yytext);}

%%

/**
 * @brief Dynamically concatenates 2 strings
 *
 * @param destination The left part of the concatenated string
 * @param source The right part of the concatenated string
 * @return null if concatenation failed, else the concatenated string
 *
 * @pre @p destination != null
 * @pre @p source != null
 *
 * @post @p destination and @p source will be left intact
 * @post Memory for the concatenated string will be allocated using `malloc`
 * (user should call `free` to free the memory)
 *
 */
char* strcat_dynamic(const char* destination, const char* source) {
  assert(destination);
  assert(source);

  char* concatenated_str =
      malloc(sizeof(char) * (strlen(destination) + strlen(source) + 1));

  if (!concatenated_str) {
    return NULL;
  }

  concatenated_str = strcpy(concatenated_str, destination);
  concatenated_str = strcat(concatenated_str, source);

  assert(concatenated_str);
  assert(!strncmp(concatenated_str, destination, strlen(destination)));
  assert(
      !strncmp(&concatenated_str[strlen(destination)], source, strlen(source)));
  return concatenated_str;
}

void concat_content_of_token(alpha_token_t token, const char* src_content) {
	RUNTIME_ASSERT(token);
	RUNTIME_ASSERT(src_content);

	const char* token_content = alpha_token_getContent(token);
	char* temp_str = strcat_dynamic(token_content, src_content);
	RUNTIME_ASSERT(temp_str);

	alpha_token_setContent(temp_str);

	free(temp_str);
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
