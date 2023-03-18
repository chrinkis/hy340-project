#pragma once

namespace alpha {
namespace token {

namespace category {
enum Category {
  INTEGER,
  FLOAT,
  STRING,
  IDENTIFIER,
  ONE_LINE_COMMENT,
  BLOCK_COMMENT,
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
  ASSIGN,               /*| =  |*/
  PLUS,                 /*| +  |*/
  MINUS,                /*| -  |*/
  STAR,                 /*| *  |*/
  DIV,                  /*| /  |*/
  MOD,                  /*| %  |*/
  EQUALS,               /*| == |*/
  NOT_EQUALS,           /*| != |*/
  PLUS_PLUS,            /*| ++ |*/
  MINUS_MINUS,          /*| -- |*/
  GREATER,              /*| >  |*/
  LESS,                 /*| <  |*/
  GREATER_EQUALS,       /*| >= |*/
  LESS_EQUALS,          /*| <= |*/
  LEFT_CURLY_BRACKET,   /*| {  |*/
  RIGHT_CURLY_BRACKET,  /*| }  |*/
  LEFT_SQUARE_BRACKET,  /*| [  |*/
  RIGHT_SQUARE_BRACKET, /*| ]  |*/
  LEFT_PARENTHESIS,     /*| (  |*/
  RIGHT_PARENTHESIS,    /*| )  |*/
  SEMICOLON,            /*| ;  |*/
  COMMA,                /*| ,  |*/
  COLON,                /*| :  |*/
  DOUBLE_COLON,         /*| :: |*/
  DOT,                  /*| .  |*/
  DOUBLE_DOT,           /*| .. |*/
};
}

}  // namespace token
}  // namespace alpha
