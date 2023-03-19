#include <alpha/lex/scanner.h>
#include <alpha/lex/status.h>
#include <alpha/token/token.h>

#include <assert.h>
#include <fstream>
#include <iostream>

using namespace alpha;
using Scanner = lex::Scanner;
using Token = token::Token;
using Category = token::category::Category;
using Status = lex::status::Status;

void print_alpha_token(const Token& token, std::ostream output_stream) {
  assert(output_stream);

  output_stream << "%d:\t" << token.get_sequence_number();
  output_stream << "#%d:\t" << token.get_line();
  output_stream << "\"%s\"\t" << token.get_content();

  switch (token.get_category()) {
    case Category::INTEGER:
      output_stream << "CONST_INT\t%s\t<-integer" << token.get_content();
      break;
    case Category::FLOAT:
      output_stream << "CONST_REAL\t%s\t<-float" << token.get_content();
      break;
    case Category::STRING:
      output_stream << "STRING\t%s\t<-char*" << token.get_content();
      break;
    case Category::IDENTIFIER:
      output_stream << "ID\t%s\t<-char*" << token.get_content();
      break;
    case Category::ONE_LINE_COMMENT:
      output_stream << "COMMENT\tLINE_COMMENT\t<-enumerated";
      break;
    case Category::BLOCK_COMMENT:
      output_stream << "COMMENT\tBLOCK_COMMENT\t<-enumerated";
      break;
    case Category::IF:
      output_stream << "COMMENT\tIF\t<-enumerated";
      break;
    case Category::ELSE:
      output_stream << "KEYWORD\tELSE\t<-enumerated";
      break;
    case Category::WHILE:
      output_stream << "KEYWORD\tWHILE\t<-enumerated";
      break;
    case Category::FOR:
      output_stream << "KEYWORD\tFOR\t<-enumerated";
      break;
    case Category::FUNCTION:
      output_stream << "KEYWORD\tFUNCTION\t<-enumerated";
      break;
    case Category::RETURN:
      output_stream << "KEYWORD\tRETURN\t<-enumerated";
      break;
    case Category::BREAK:
      output_stream << "KEYWORD\tBREAK\t<-enumerated";
      break;
    case Category::CONTINUE:
      output_stream << "KEYWORD\tCONTINUE\t<-enumerated";
      break;
    case Category::AND:
      output_stream << "KEYWORD\tAND\t<-enumerated";
      break;
    case Category::NOT:
      output_stream << "KEYWORD\tNOT\t<-enumerated";
      break;
    case Category::OR:
      output_stream << "KEYWORD\tOR\t<-enumerated";
      break;
    case Category::LOCAL:
      output_stream << "KEYWORD\tLOCAL\t<-enumerated";
      break;
    case Category::TRUE:
      output_stream << "KEYWORD\tTRUE\t<-enumerated";
      break;
    case Category::FALSE:
      output_stream << "KEYWORD\tFALSE\t<-enumerated";
      break;
    case Category::NIL:
      output_stream << "KEYWORD\tNIL\t<-enumerated";
      break;
    case Category::ASSIGN:
      output_stream << "OPERATOR\tASSIGN\t<-enumerated";
      break;
    case Category::PLUS:
      output_stream << "OPERATOR\tPLUS\t<-enumerated";
      break;
    case Category::MINUS:
      output_stream << "OPERATOR\tMINUS\t<-enumerated";
      break;
    case Category::STAR:
      output_stream << "OPERATOR\tSTAR\t<-enumerated";
      break;
    case Category::DIV:
      output_stream << "OPERATOR\tDIV\t<-enumerated";
      break;
    case Category::MOD:
      output_stream << "OPERATOR\tMOD\t<-enumerated";
      break;
    case Category::EQUALS:
      output_stream << "OPERATOR\tEQUALS\t<-enumerated";
      break;
    case Category::NOT_EQUALS:
      output_stream << "OPERATOR\tNOT_EQUALS\t<-enumerated";
      break;
    case Category::PLUS_PLUS:
      output_stream << "OPERATOR\tPLUS_PLUS\t<-enumerated";
      break;
    case Category::MINUS_MINUS:
      output_stream << "OPERATOR\tMINUS_MINUS\t<-enumerated";
      break;
    case Category::GREATER:
      output_stream << "OPERATOR\tGREATER\t<-enumerated";
      break;
    case Category::LESS:
      output_stream << "OPERATOR\tLESS\t<-enumerated";
      break;
    case Category::GREATER_EQUALS:
      output_stream << "OPERATOR\tGREATER_EQUALS\t<-enumerated";
      break;
    case Category::LESS_EQUALS:
      output_stream << "OPERATOR\tLESS_EQUALS\t<-enumerated";
      break;
    case Category::LEFT_CURLY_BRACKET:
      output_stream << "PUNCTUATION\tLEFT_CURLY_BRACKET\t<-enumerated";
      break;
    case Category::RIGHT_CURLY_BRACKET:
      output_stream << "PUNCTUATION\tRIGHT_CURLY_BRACKET\t<-enumerated";
      break;
    case Category::LEFT_SQUARE_BRACKET:
      output_stream << "PUNCTUATION\tLEFT_SQUARE_BRACKET\t<-enumerated";
      break;
    case Category::RIGHT_SQUARE_BRACKET:
      output_stream << "PUNCTUATION\tRIGHT_SQUARE_BRACKET\t<-enumerated";
      break;
    case Category::LEFT_PARENTHESIS:
      output_stream << "PUNCTUATION\tLEFT_PARENTHESIS\t<-enumerated";
      break;
    case Category::RIGHT_PARENTHESIS:
      output_stream << "PUNCTUATION\tRIGHT_PARENTHESIS\t<-enumerated";
      break;
    case Category::SEMICOLON:
      output_stream << "PUNCTUATION\tSEMICOLON\t<-enumerated";
      break;
    case Category::COMMA:
      output_stream << "PUNCTUATION\tCOMMA\t<-enumerated";
      break;
    case Category::COLON:
      output_stream << "PUNCTUATION\tCOLON\t<-enumerated";
      break;
    case Category::DOUBLE_COLON:
      output_stream << "PUNCTUATION\tDOUBLE_COLON\t<-enumerated";
      break;
    case Category::DOT:
      output_stream << "PUNCTUATION\tDOT\t<-enumerated";
      break;
    case Category::DOUBLE_DOT:
      output_stream << "PUNCTUATION\tDOUBLE_DOT\t<-enumerated";
      break;
    default:
      fprintf(stderr, "Unkown token category!");
      break;
  }

  output_stream << "\n";
}

int main(int argc, char** argv) {
  assert((argc >= 0) && (argc <= 3));

  std::istream* input_stream = &std::cin;
  std::ifstream input_file_stream;

  if (argc > 1) {
    input_file_stream.open(argv[1]);

    if (!input_file_stream.is_open()) {
      std::cerr << "Cannot read file: " << argv[1] << "\n";
      return 1;
    }

    input_stream = &input_file_stream;
  }

  std::ostream* output_stream = &std::cout;
  std::ofstream output_file_stream;

  if (argc > 2) {
    output_file_stream.open(argv[2]);

    if (!output_file_stream.is_open()) {
      std::cerr << "Cannot write file: " << argv[2] << "\n";
      return 1;
    }

    output_stream = &output_file_stream;
  }

  Scanner scanner(input_stream);

  do {
    scanner.yylex();

    switch (scanner.get_status()) {
      case Status::NOT_CLOSED_STRING:
        std::cerr << "ERROR NOT CLOSING STRING\n";
        break;
      case Status::UNKNOWN_ESCAPE_CHAR:
        std::cerr << "ERROR INVALID ESCAPE CHARACTER\n";
        break;
      case Status::NOT_CLOSED_COMMENT:
        std::cerr << "ERROR NOT CLOSING COMMENT\n";
        break;
      case Status::UNKNOWN_TOKEN:
        std::cerr << "ERROR UNKOWN TOKEN\n";
        break;
      case Status::SUCCESS:
        print_alpha_token(scanner.get_token(), &output_stream);
        break;
      default:;
    }

  } while (scanner.get_status() != Status::END_OF_FILE);

  /* Close open file streams (if any) */
  if (output_file_stream.is_open()) {
    output_file_stream.close();
  }

  if (input_file_stream.is_open()) {
    input_file_stream.close();
  }

  return 0;
}
