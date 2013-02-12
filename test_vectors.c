// $Id: test_vectors.c 565 2011-03-09 01:07:22Z phf $

#include "vectors.h"

#include <stdio.h>
#include <stdlib.h>

struct data {
  int a, b, c;
  double d;
  char *s;
};

int main(void) {
  size_t i;

  vector_t v;
  vector_new(&v, sizeof(struct data));
  vector_dump(&v);

  for (i = 0; i < 40; i++) {
    struct data x = {i, i+2, i*2, -i, NULL};
    vector_push(&v, &x);
    vector_dump(&v);
  }

  for (i = 0; i < v.length; i++) {
    struct data x;
    vector_get(&v, i, &x);
    printf("%zu: {%d %d %d %g %s}\n", i, x.a, x.b, x.c, x.d, x.s);
    x.d = -x.d;
    vector_put(&v, i, &x);
  }

  for (i = 0; i < v.length; i++) {
    struct data x;
    vector_get(&v, i, &x);
    printf("%zu: {%d %d %d %g %s}\n", i, x.a, x.b, x.c, x.d, x.s);
  }

  vector_delete(&v);
  return EXIT_SUCCESS;
}
