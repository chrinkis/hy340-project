%{
#include<assert.h>
#include "../../include/token/alpha_token_t.h"
#include "../../include/token/alpha_token_category.h"

#define RUNTIME_ASSERT(what) assert(what)
#define YY_DECL int alpha_yylex(void* yylval)
%}

/* Flex options */
%option noyywrap
%option yylineno

/* Flex macros */
delimeter	[ \t\n]
whitespaces	[delimeter]+
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

<STRING>[^\\\"]*	/* read until escape char or end of string char */
<STRING>\"			BEGIN(INITIAL); /* end of string */
<STRING>\\			BEGIN(ESCAPE); /* escape char follows */
<ESCAPE>[\"nt\\]	BEGIN(STRING); /* which escaped char? */
<ESCAPE>[.]*		/* Unknown escaped charachter (No mans land) */
\"					BEGIN(STRING); /* String literal begins */

{whitespaces}		{fprintf(stderr, "ignore\n", yytext);}
"="					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_ASSIGN);
"+"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_PLUS);
"-"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_MINUS);
"*"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_STAR);
"/"					yylval = add_new_token(yylval, yytext, ALPHA_TOKEN_DIV);
"%"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"=="				{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"!="				{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"++"				{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"--"				{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
">"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"<"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
">="				{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"<="				{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"{"					{fprintf(stderr, "Recognized punctuation with content: %s\n", yytext);}
"}"					{fprintf(stderr, "Recognized punctuation with content: %s\n", yytext);}
"["					{fprintf(stderr, "Recognized punctuation with content: %s\n", yytext);}
"]"					{fprintf(stderr, "Recognized punctuation with content: %s\n", yytext);}
"("					{fprintf(stderr, "Recognized punctuation with content: %s\n", yytext);}
")"					{fprintf(stderr, "Recognized punctuation with content: %s\n", yytext);}
{real}				{fprintf(stderr, "Recognies real number with content: %s\n", yytext);}

{integer}
"if"
"else"
"while"
"for"
"function"
"return"
"break"
"continue"
"and"
"not"
"or"
"local"
"true"
"false"
"nil"

";"
","
"::"
":"
".."
"."

{identifier}

"//".*				{fprintf(stderr, "Recognized oneline comment with content: %s\n", yytext);}
"/*"				{fprintf(stderr, "Recognized multiline comment with with line range: %d-", yylineno);
					 BEGIN(COMMENT);
					}
<COMMENT>[^*]*		/* eat anything that's not a '*' = do nothing */
<COMMENT>"*"+[^*/]*	/* eat anything that's not a '*' = do nothing */
<COMMENT>"*"+"/"*	{fprintf(stderr, "%d\n", yylineno);
					 BEGIN(INITIAL);
					}
.					{fprintf(stderr, "Cannot match character '%s' with any rule\n", yytext);}

%%

alpha_token_t add_new_token(alpha_token_t tail, const char* text, alpha_token_category category) {
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
