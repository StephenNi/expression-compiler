// $Id: main.c 575 2011-03-10 13:08:15Z phf $

#include "vectors.h"
#include "strings.h"
#include "tokens.h"
#include "scanner.h"
#include "nodes.h"
#include "parser.h"
#include "interpreter.h"
#include "spim.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int c;
  string_t source;
  vector_t tokens;
  node_t *ast;
  string_t code;

  if (argc != 2 || !strchr("rspic", argv[1][0])) {
    printf("usage: %s _r_eader _s_canner _p_arser _i_nterpreter _c_ompiler\n", argv[0]);
    return EXIT_FAILURE;
  }

  string_new(&source);
  while ((c = getchar()) != EOF) {
    string_append_char(&source, c);
  }

  if (argv[1][0] == 'r') {
    string_dump(&source);
    goto reader;
  }

  tokens = scan(&source);

  if (argv[1][0] == 's') {
    size_t i;
    for (i = 0; i < tokens.length; i++) {
      token_t t;
      vector_get(&tokens, i, &t);
      token_dump(&t);
    }
    goto scanner;
  }

  ast = parse(&tokens);

  if (argv[1][0] == 'p') {
    node_dump(ast);
    goto parser;
  }

  if (argv[1][0] == 'i') {
    printf("%d\n", eval(ast));
    goto parser;
  }

  if (argv[1][0] == 'c') {
    string_new(&code);
    generate(ast, &code);
    printf("%s", code.data);
    string_delete(&code);
  }

parser:
  node_delete(ast);
scanner:
  vector_delete(&tokens);
reader:
  string_delete(&source);
  return EXIT_SUCCESS;
}
