// $Id: test_parser.c 565 2011-03-09 01:07:22Z phf $

#include "vectors.h"
#include "strings.h"
#include "tokens.h"
#include "scanner.h"
#include "nodes.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t i;
  string_t src;
  vector_t toks;
  node_t *ast;
  string_str(&src, "(1+2)*3+4");
  puts(src.data);
  toks = scan(&src);
  vector_dump(&toks);
  for (i = 0; i < toks.length; i++) {
    token_t tok;
    vector_get(&toks, i, &tok);
    token_dump(&tok);
  }
  ast = parse(&toks);
  node_dump(ast);
  node_delete(ast);
  vector_delete(&toks);
  string_delete(&src);
  return EXIT_SUCCESS;
}
