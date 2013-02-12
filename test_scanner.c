// $Id: test_scanner.c 533 2010-05-08 05:19:24Z phf $

#include "vectors.h"
#include "strings.h"
#include "tokens.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t i;
  string_t src;
  vector_t toks;
  string_str(&src, "(1+2)*3+4");
  puts(src.data);
  toks = scan(&src);
  vector_dump(&toks);
  for (i = 0; i < toks.length; i++) {
    token_t tok;
    vector_get(&toks, i, &tok);
    token_dump(&tok);
  }
  vector_delete(&toks);
  string_delete(&src);
  return EXIT_SUCCESS;
}
