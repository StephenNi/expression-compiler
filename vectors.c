// $Id: vectors.c 565 2011-03-09 01:07:22Z phf $

#include "vectors.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MEMSET_PATTERN 'X'

static const size_t DEFAULT_CAPACITY = 16;

void vector_new(vector_t *v, size_t s) {
  vector_new_capacity(v, DEFAULT_CAPACITY, s);
}

void vector_new_capacity(vector_t *v, size_t c, size_t s) {
  size_t total;

  assert(v != NULL && c > 0 && s > 0);

  v->length = 0;
  v->element = s;
  v->capacity = c;

  total = v->element * v->capacity;
  v->data = malloc(total);
  assert(v->data != NULL);

  memset(v->data, MEMSET_PATTERN, total);
}

void vector_delete(/*@only@*/ vector_t *v) {
  assert(v != NULL && v->data != NULL);

  free(v->data);

  v->data = NULL;
  v->length = -1;
  v->element = -1;
  v->capacity = -1;
}

void vector_dump(const vector_t *v) {
  printf(
    "vector_t<data: %p size: %zu length: %zu capacity: %zu>\n",
    v->data, v->element, v->length, v->capacity
  );
}

static bool vector_full(const vector_t *v) {
  return v->length == v->capacity;
}

static void vector_grow(vector_t *v) {
  size_t bigger = v->capacity * 2;

  char *new = malloc(v->element * bigger);
  assert(new != NULL);
  memset(new, MEMSET_PATTERN, v->element * bigger);
  memcpy(new, v->data, v->element * v->capacity);

  free(v->data);

  v->data = new;
  v->capacity = bigger;
}

void vector_push(vector_t *v, const void *e) {
  assert(v != NULL && v->data != NULL);
  assert(e != NULL);

  if (vector_full(v)) {
    vector_grow(v);
  }

  memcpy(v->data + v->length*v->element, e, v->element);
  v->length += 1;
}

void vector_pop(vector_t *v) {
  assert(v != NULL && v->data != NULL && v->length > 0);
  v->length -= 1;
}

void vector_get(const vector_t *v, size_t i, void *e) {
  assert(v != NULL && v->data != NULL);
  assert(i < v->length && e != NULL);
  memcpy(e, v->data + i*v->element, v->element);
}

void vector_put(vector_t *v, size_t i, const void *e) {
  assert(v != NULL && v->data != NULL);
  assert(i < v->length && e != NULL);
  memcpy(v->data + i*v->element, e, v->element);
}
