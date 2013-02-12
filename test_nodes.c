// $Id: test_nodes.c 565 2011-03-09 01:07:22Z phf $

#include "nodes.h"

#include <stdio.h>
#include <stdlib.h>

void test_static(void) {
  node_t t;
  node_t q;
  node_t r;

  t.kind = INTEGER;
  t.value = 42;
  node_dump(&t);

  q.kind = INTEGER;
  q.value = 10;
  node_dump(&q);

  r.kind = PLUS;
  r.left = &t;
  r.right = &q;
  node_dump(&r);
}

void test_dynamic(void) {
  node_t *p, *l, *r;
  p = node_new(PLUS);
  l = node_new(INTEGER);
  l->value = 42;
  r = node_new(INTEGER);
  r->value = 10;
  p->left = l;
  p->right = r;
  node_dump(p);
  node_delete(p);
}

int main(void) {
  test_static();
  test_dynamic();
  return EXIT_SUCCESS;
}
