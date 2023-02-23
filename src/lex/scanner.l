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


%%

{whitespaces}		{fprintf(stderr, "ignore\n", yytext);}
"="					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"+"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"-"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"*"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
"/"					{fprintf(stderr, "Recognized operator with content: %s\n", yytext);}
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

int main(int argc, char **argv) {
  if (argc > 1) {
    if (!(yyin = fopen(argv[1], "r"))) {
      fprintf(stderr, "Cannot read file: %s\n", argv[1]);
      return 1;
    }
  } else {
    yyin = stdin;
  }

  yylex();
  return 0;
}
