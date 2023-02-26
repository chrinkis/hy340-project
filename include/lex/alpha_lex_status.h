#ifndef __ALPHA_LEX_STATUS_H__
#define __ALPHA_LEX_STATUS_H__

enum _alpha_lex_status {
  ALPHA_LEX_STATUS_SUCCESS,
  ALPHA_LEX_STATUS_NOT_CLOSED_STRING,
  ALPHA_LEX_STATUS_NOT_CLOSED_COMMENT,
  ALPHA_LEX_STATUS_UNKNOWN_ESCAPE_CHAR,
  ALPHA_LEX_STATUS_UNKNOWN_TOKEN,
};

#endif
