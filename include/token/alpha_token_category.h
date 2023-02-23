#ifndef __ALPHA_TOKEN_CATEGORY__
#define __ALPHA_TOKEN_CATEGORY__

enum alpha_token_category {
  INTEGER,
  FLOAT,
  STRING,
  IDENTIFIER,
  COMMENT,
  IF,
  ELSE,
  WHILE,
  FOR,
  FUNCTION,
  RETURN,
  BREAK,
  CONTINUE,
  AND,
  NOT,
  OR,
  LOCAL,
  TRUE,
  FALSE,
  NIL,
  ASSIGN,                    /*| =  |*/
  PLUS,                      /*| +  |*/
  MINUS,                     /*| -  |*/
  STAR,                      /*| *  |*/
  DIV,                       /*| /  |*/
  MOD,                       /*| %  |*/
  EQUALS,                    /*| == |*/
  NOT_EQUALS,                /*| != |*/
  PLUS_PLUS,                 /*| ++ |*/
  MINUS_MINUS,               /*| -- |*/
  GREATER,                   /*| >  |*/
  LESS,                      /*| <  |*/
  GREATER_EQUALS,            /*| >= |*/
  LESS_EQUALS,               /*| <= |*/
  LEFT_CURLY_BRACKET,        /*| {  |*/
  RIGHT_CURLY_BRACKET,       /*| }  |*/
  LEFT_SQUARE_BRACKET,       /*| [  |*/
  RIGHT_SQUARE_BRACKET,      /*| ]  |*/
  LEFT_PARENTHESIS_BRACKET,  /*| (  |*/
  RIGHT_PARENTHESIS_BRACKET, /*| )  |*/
  SEMICOLON,                 /*| ;  |*/
  COMMA,                     /*| ,  |*/
  COLON,                     /*| :  |*/
  DOUBLE_COLON,              /*| :: |*/
  DOT,                       /*| .  |*/
  DOUBLE_DOT,                /*| .. |*/
};

#endif
