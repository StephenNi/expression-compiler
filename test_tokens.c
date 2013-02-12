// $Id: test_tokens.c 520 2010-04-23 16:53:02Z phf $

#include "tokens.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  token_t t;
  t.kind = INTEGER;
  t.value = 42;
  token_dump(&t);
  t.kind = MINUS;
  token_dump(&t);
  return EXIT_SUCCESS;
}
