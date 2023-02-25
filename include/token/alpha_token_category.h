#ifndef __ALPHA_TOKEN_CATEGORY__
#define __ALPHA_TOKEN_CATEGORY__

typedef enum {
  ALPHA_TOKEN_INTEGER,
  ALPHA_TOKEN_FLOAT,
  ALPHA_TOKEN_STRING,
  ALPHA_TOKEN_IDENTIFIER,
  ALPHA_TOKEN_COMMENT,
  ALPHA_TOKEN_IF,
  ALPHA_TOKEN_ELSE,
  ALPHA_TOKEN_WHILE,
  ALPHA_TOKEN_FOR,
  ALPHA_TOKEN_FUNCTION,
  ALPHA_TOKEN_RETURN,
  ALPHA_TOKEN_BREAK,
  ALPHA_TOKEN_CONTINUE,
  ALPHA_TOKEN_AND,
  ALPHA_TOKEN_NOT,
  ALPHA_TOKEN_OR,
  ALPHA_TOKEN_LOCAL,
  ALPHA_TOKEN_TRUE,
  ALPHA_TOKEN_FALSE,
  ALPHA_TOKEN_NIL,
  ALPHA_TOKEN_ASSIGN,               /*| =  |*/
  ALPHA_TOKEN_PLUS,                 /*| +  |*/
  ALPHA_TOKEN_MINUS,                /*| -  |*/
  ALPHA_TOKEN_STAR,                 /*| *  |*/
  ALPHA_TOKEN_DIV,                  /*| /  |*/
  ALPHA_TOKEN_MOD,                  /*| %  |*/
  ALPHA_TOKEN_EQUALS,               /*| == |*/
  ALPHA_TOKEN_NOT_EQUALS,           /*| != |*/
  ALPHA_TOKEN_PLUS_PLUS,            /*| ++ |*/
  ALPHA_TOKEN_MINUS_MINUS,          /*| -- |*/
  ALPHA_TOKEN_GREATER,              /*| >  |*/
  ALPHA_TOKEN_LESS,                 /*| <  |*/
  ALPHA_TOKEN_GREATER_EQUALS,       /*| >= |*/
  ALPHA_TOKEN_LESS_EQUALS,          /*| <= |*/
  ALPHA_TOKEN_LEFT_CURLY_BRACKET,   /*| {  |*/
  ALPHA_TOKEN_RIGHT_CURLY_BRACKET,  /*| }  |*/
  ALPHA_TOKEN_LEFT_SQUARE_BRACKET,  /*| [  |*/
  ALPHA_TOKEN_RIGHT_SQUARE_BRACKET, /*| ]  |*/
  ALPHA_TOKEN_LEFT_PARENTHESIS,     /*| (  |*/
  ALPHA_TOKEN_RIGHT_PARENTHESIS,    /*| )  |*/
  ALPHA_TOKEN_SEMICOLON,            /*| ;  |*/
  ALPHA_TOKEN_COMMA,                /*| ,  |*/
  ALPHA_TOKEN_COLON,                /*| :  |*/
  ALPHA_TOKEN_DOUBLE_COLON,         /*| :: |*/
  ALPHA_TOKEN_DOT,                  /*| .  |*/
  ALPHA_TOKEN_DOUBLE_DOT,           /*| .. |*/
} alpha_token_category_t;

#endif
