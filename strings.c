// $Id: strings.c 565 2011-03-09 01:07:22Z phf $

#include "strings.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))

static char THE_NUL = 0;

// Closest power of 2.
//
// This is a treat! Check Warren's "Hacker's Delight" for
// the details, pp. 46. Oh, this assumes a 32 bit machine,
// add another "shift line" for 64 bit.
static size_t clp2(size_t n) {
  n = n - 1;
  n = n | (n >> 1);
  n = n | (n >> 2);
  n = n | (n >> 4);
  n = n | (n >> 8);
  n = n | (n >> 16);
  n = n + 1;
  return n;
}

void string_new(string_t *s) {
  vector_new(s, sizeof(char));
  vector_push(s, &THE_NUL);
}

void string_str(string_t *s, const char *chars) {
  size_t length = strlen(chars);
  size_t capacity = clp2(length+1);
  vector_new_capacity(s, capacity, sizeof(char));
  strncpy(s->data, chars, length);
  s->length = length;
  vector_push(s, &THE_NUL);
}

void string_delete(/*@only@*/ string_t *s) {
  vector_delete(s);
}

void string_dump(const string_t *s) {
  printf(
    "string_t<data: \"%s\" length: %zu capacity: %zu>\n",
    s->data, s->length, s->capacity
  );
}

void string_append_char(string_t *s, char c) {
  vector_pop(s);
  vector_push(s, &c);
  vector_push(s, &THE_NUL);
}

void string_append_chars(string_t *s, const char *c) {
  // TODO: horribly slow...
  while (*c != '\0') {
    string_append_char(s, *c);
    c++;
  }
}

int string_compare(const string_t *s, const string_t *t) {
  return strncmp(s->data, t->data, MAX(s->length, t->length));
}
