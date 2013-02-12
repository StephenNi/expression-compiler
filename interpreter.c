// $Id: interpreter.c 565 2011-03-09 01:07:22Z phf $

#include "interpreter.h"

#include <stdbool.h>
#include <assert.h>

static bool operator(node_kind_t kind) {
  // requires kinds to be ordered appropriately
  return (PLUS <= kind && kind <= SLASH);
}

int eval(const node_t *ast) {
  int left, right;
  if (ast->kind == INTEGER) {
    return ast->value;
  }
  else if (operator(ast->kind)) {
    left = eval(ast->left);
    right = eval(ast->right);
    switch (ast->kind) {
      // no breaks since all cases abort call
      case PLUS:  return left + right;
      case MINUS: return left - right;
      case TIMES: return left * right;
      case SLASH: return left / right;
      default: assert(0); // shut up warning
    }
  }
  else {
    // invalid kind in abstract syntax tree
    assert(0);
  }
}
