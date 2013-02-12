// $Id: tokens.h 565 2011-03-09 01:07:22Z phf $

#ifndef _TOKENS_H
#define _TOKENS_H

// Token kinds
typedef enum {
  _FIRST=-1, PLUS, MINUS, TIMES, SLASH, OPEN, CLOSE, INTEGER, _LAST
} token_kind_t;

// Representation of a token
typedef struct {
  token_kind_t kind;
  int value;
} token_t;

// Dump token to stdout (for debugging).
void token_dump(const token_t *t);

#endif
