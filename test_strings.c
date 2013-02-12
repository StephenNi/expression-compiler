// $Id: test_strings.c 565 2011-03-09 01:07:22Z phf $

#include "strings.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  char c;
  string_t t;
  string_t s;

  string_new(&s);
  string_dump(&s);

  for (i = 0; i < 3; i++) {
    for (c = 'a'; c <= 'z'; c++) {
      string_append_char(&s, c);
      string_dump(&s);
    }
  }

  string_str(&t, "Just a test for");
  string_dump(&t);

  for (c = 'a'; c <= 'z'; c++) {
    string_append_char(&t, c);
    string_dump(&t);
  }

  string_append_chars(&t, "and another string");
  string_dump(&t);
  string_append_chars(&t, "and another string");
  string_dump(&t);
  string_append_chars(&t, "and another string");
  string_dump(&t);
  string_append_chars(&t, "and another string");
  string_dump(&t);
  string_append_chars(&t, "and another string");
  string_dump(&t);

  printf("%d\n", string_compare(&s, &t));
  printf("%d\n", string_compare(&t, &s));
  printf("%d\n", string_compare(&t, &t));
  printf("%d\n", string_compare(&s, &s));

  string_delete(&t);
  string_delete(&s);
  return EXIT_SUCCESS;
}
