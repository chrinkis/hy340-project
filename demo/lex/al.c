#include <alpha_token.h>
#include <assert.h>
#include <stdio.h>

void print_alpha_token(const alpha_token_t token, FILE* stream) {
  assert(token);

  fprintf(stream, "%d:\t", alpha_token_getSequenceNumber(token));
  fprintf(stream, "#%d\t", alpha_token_getLine(token));
  fprintf(stream, "\"%s\"\t", alpha_token_getContent(token));

  switch (alpha_token_getCategory(token)) {
    case ALPHA_TOKEN_INTEGER:
      fprintf(stream, "CONST_INT\t%s\t<-integer",
              alpha_token_getContent(token));
      break;
    case ALPHA_TOKEN_FLOAT:
      fprintf(stream, "CONST_REAL\t%s\t<-float", alpha_token_getContent(token));
      break;
    case ALPHA_TOKEN_STRING:
      fprintf(stream, "STRING\t\"%s\"\t<-char*", alpha_token_getContent(token));
      break;
    case ALPHA_TOKEN_IDENTIFIER:
      fprintf(stream, "ID\t\"%s\"\t<-char*", alpha_token_getContent(token));
      break;
    case ALPHA_TOKEN_COMMENT:
      fprintf(stream, "COMMENT\tALL_COMMENTS\t<-enumerated");
      break;
    case ALPHA_TOKEN_IF:
      fprintf(stream, "KEYWORD\tIF\t<-enumerated");
      break;
    case ALPHA_TOKEN_ELSE:
      fprintf(stream, "KEYWORD\tELSE\t<-enumerated");
      break;
    case ALPHA_TOKEN_WHILE:
      fprintf(stream, "KEYWORD\tWHILE\t<-enumerated");
      break;
    case ALPHA_TOKEN_FOR:
      fprintf(stream, "KEYWORD\tFOR\t<-enumerated");
      break;
    case ALPHA_TOKEN_FUNCTION:
      fprintf(stream, "KEYWORD\tFUNCTION\t<-enumerated");
      break;
    case ALPHA_TOKEN_RETURN:
      fprintf(stream, "KEYWORD\tRETURN\t<-enumerated");
      break;
    case ALPHA_TOKEN_BREAK:
      fprintf(stream, "KEYWORD\tBREAK\t<-enumerated");
      break;
    case ALPHA_TOKEN_CONTINUE:
      fprintf(stream, "KEYWORD\tCONTINUE\t<-enumerated");
      break;
    case ALPHA_TOKEN_AND:
      fprintf(stream, "KEYWORD\tAND\t<-enumerated");
      break;
    case ALPHA_TOKEN_NOT:
      fprintf(stream, "KEYWORD\tNOT\t<-enumerated");
      break;
    case ALPHA_TOKEN_OR:
      fprintf(stream, "KEYWORD\tOR\t<-enumerated");
      break;
    case ALPHA_TOKEN_LOCAL:
      fprintf(stream, "KEYWORD\tLOCAL\t<-enumerated");
      break;
    case ALPHA_TOKEN_TRUE:
      fprintf(stream, "KEYWORD\tTRUE\t<-enumerated");
      break;
    case ALPHA_TOKEN_FALSE:
      fprintf(stream, "KEYWORD\tFALSE\t<-enumerated");
      break;
    case ALPHA_TOKEN_NIL:
      fprintf(stream, "KEYWORD\tNIL\t<-enumerated");
      break;
    case ALPHA_TOKEN_ASSIGN: /*| =  |*/
      fprintf(stream, "OPERATOR\tASSIGN\t<-enumerated");
      break;
    case ALPHA_TOKEN_PLUS: /*| +  |*/
      fprintf(stream, "OPERATOR\tPLUS\t<-enumerated");
      break;
    case ALPHA_TOKEN_MINUS: /*| -  |*/
      fprintf(stream, "OPERATOR\tMINUS\t<-enumerated");
      break;
    case ALPHA_TOKEN_STAR: /*| *  |*/
      fprintf(stream, "OPERATOR\tSTAR\t<-enumerated");
      break;
    case ALPHA_TOKEN_DIV: /*| /  |*/
      fprintf(stream, "OPERATOR\tDIV\t<-enumerated");
      break;
    case ALPHA_TOKEN_MOD: /*| %  |*/
      fprintf(stream, "OPERATOR\tMOD\t<-enumerated");
      break;
    case ALPHA_TOKEN_EQUALS: /*| == |*/
      fprintf(stream, "OPERATOR\tEQUALS\t<-enumerated");
      break;
    case ALPHA_TOKEN_NOT_EQUALS: /*| != |*/
      fprintf(stream, "OPERATOR\tNOT_EQUALS\t<-enumerated");
      break;
    case ALPHA_TOKEN_PLUS_PLUS: /*| ++ |*/
      fprintf(stream, "OPERATOR\tPLUS_PLUS\t<-enumerated");
      break;
    case ALPHA_TOKEN_MINUS_MINUS: /*| -- |*/
      fprintf(stream, "OPERATOR\tMINUS_MINUS\t<-enumerated");
      break;
    case ALPHA_TOKEN_GREATER: /*| >  |*/
      fprintf(stream, "OPERATOR\tGREATER\t<-enumerated");
      break;
    case ALPHA_TOKEN_LESS: /*| <  |*/
      fprintf(stream, "OPERATOR\tLESS\t<-enumerated");
      break;
    case ALPHA_TOKEN_GREATER_EQUALS: /*| >= |*/
      fprintf(stream, "OPERATOR\tGREATER_EQUALS\t<-enumerated");
      break;
    case ALPHA_TOKEN_LESS_EQUALS: /*| <= |*/
      fprintf(stream, "OPERATOR\tLESS_EQUALS\t<-enumerated");
      break;
    case ALPHA_TOKEN_LEFT_CURLY_BRACKET: /*| {  |*/
      fprintf(stream, "PUNCTUATION\tLEFT_CURLY_BRACKET\t<-enumerated");
      break;
    case ALPHA_TOKEN_RIGHT_CURLY_BRACKET: /*| }  |*/
      fprintf(stream, "PUNCTUATION\tRIGHT_CURLY_BRACKET\t<-enumerated");
      break;
    case ALPHA_TOKEN_LEFT_SQUARE_BRACKET: /*| [  |*/
      fprintf(stream, "PUNCTUATION\tLEFT_SQUARE_BRACKET\t<-enumerated");
      break;
    case ALPHA_TOKEN_RIGHT_SQUARE_BRACKET: /*| ]  |*/
      fprintf(stream, "PUNCTUATION\tRIGHT_SQUARE_BRACKET\t<-enumerated");
      break;
    case ALPHA_TOKEN_LEFT_PARENTHESIS: /*| (  |*/
      fprintf(stream, "PUNCTUATION\tLEFT_PARENTHESIS\t<-enumerated");
      break;
    case ALPHA_TOKEN_RIGHT_PARENTHESIS: /*| )  |*/
      fprintf(stream, "PUNCTUATION\tRIGHT_PARENTHESIS\t<-enumerated");
      break;
    case ALPHA_TOKEN_SEMICOLON: /*| ;  |*/
      fprintf(stream, "PUNCTUATION\tSEMICOLON\t<-enumerated");
      break;
    case ALPHA_TOKEN_COMMA: /*| ,  |*/
      fprintf(stream, "PUNCTUATION\tCOMMA\t<-enumerated");
      break;
    case ALPHA_TOKEN_COLON: /*| :  |*/
      fprintf(stream, "PUNCTUATION\tCOLON\t<-enumerated");
      break;
    case ALPHA_TOKEN_DOUBLE_COLON: /*| :: |*/
      fprintf(stream, "PUNCTUATION\tDOUBLE_COLON\t<-enumerated");
      break;
    case ALPHA_TOKEN_DOT: /*| .  |*/
      fprintf(stream, "PUNCTUATION\tDOT\t<-enumerated");
      break;
    case ALPHA_TOKEN_DOUBLE_DOT: /*| .. |*/
      fprintf(stream, "PUNCTUATION\tDOUBLE_DOT\t<-enumerated");
      break;
    default:
      fprintf(stderr, "Unkown token category!");
      break;
  }
  fprintf(stream, "\n");
}

void print_list_of_alpha_tokens(alpha_token_t head, FILE* stream) {
  assert(head);

  while (alpha_token_hasNext(head)) {
    print_alpha_token(head, stream);
    head = alpha_token_getNext(head);
  }

  print_alpha_token(head, stream);
}
