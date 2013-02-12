// $Id: nodes.c 565 2011-03-09 01:07:22Z phf $

#include "nodes.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char mapping[] = {
  [PLUS] = '+',
  [MINUS] = '-',
  [TIMES] = '*',
  [SLASH] = '/',
  [OPEN] = '(',
  [CLOSE] = ')',
};

static void real_dump(const node_t *t, int level) {
  int i;
  assert(t != NULL && (_FIRST < t->kind && t->kind < _LAST)); // TODO: allows ( )
  for (i = 0; i < level; i++) {
    printf("  ");
  }
  if (t->kind == INTEGER) {
    printf("integer<%d>\n", t->value);
  }
  else {
    printf("operator<%c>\n", mapping[t->kind]);
    real_dump(t->left, level+1);
    real_dump(t->right, level+1);
  }
}

void node_dump(const node_t *t) {
  real_dump(t, 0);
}

node_t *node_new(node_kind_t kind) {
  node_t *new = malloc(sizeof(node_t));
  memset(new, 0, sizeof(node_t));
  assert(_FIRST < kind && kind < _LAST); // TODO: allows ( )
  new->kind = kind;
  return new;
}

void node_delete(node_t *node) {
  if (node != NULL) {
    node_delete(node->left);
    node->left = NULL;
    node_delete(node->right);
    node->left = NULL;
    free(node);
  }
}
