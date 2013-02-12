// $Id: tokens.c 519 2010-04-23 16:51:14Z phf $

#include "tokens.h"

#include <stdio.h>
#include <assert.h>

static char mapping[] = {
  [PLUS] = '+',
  [MINUS] = '-',
  [TIMES] = '*',
  [SLASH] = '/',
  [OPEN] = '(',
  [CLOSE] = ')',
};

void token_dump(const token_t *t) {
  assert(t != NULL && (_FIRST < t->kind && t->kind < _LAST));
  if (t->kind == INTEGER) {
    printf("integer<%d>\n", t->value);
  }
  else {
    printf("symbol<%c>\n", mapping[t->kind]);
  }
}
