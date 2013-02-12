// $Id: scanner.c 565 2011-03-09 01:07:22Z phf $

#include "scanner.h"

#include <stdbool.h>
#include <assert.h>

// Is c whitespace?
static bool blank(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r'
      || c == '\v' || c == '\f';
}

// Is c a digit?
static bool digit(char c) {
  return ('0' <= c) && (c <= '9');
}

// Is c a special symbol?
static bool symbol(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/'
      || c == '(' || c == ')';
}

// Convert string source into a vector of tokens.
vector_t scan(string_t *source) {
  vector_t tokens;
  token_t t;
  size_t i = 0;
  size_t s = source->length-1;
  int v;

  vector_new(&tokens, sizeof(token_t));

  while (i < s) {
    if (blank(source->data[i])) {
      i += 1;
    }
    else if (digit(source->data[i])) {
      v = 0;
      while (i < s && digit(source->data[i])) {
        v = 10*v + (source->data[i] - '0');
        i += 1;
      }
      t.kind = INTEGER;
      t.value = v;
      vector_push(&tokens, &t);
    }
    else if (symbol(source->data[i])) {
      switch (source->data[i]) {
        case '+': t.kind = PLUS; break;
        case '-': t.kind = MINUS; break;
        case '*': t.kind = TIMES; break;
        case '/': t.kind = SLASH; break;
        case '(': t.kind = OPEN; break;
        case ')': t.kind = CLOSE; break;
        default: assert(false); break;
      }
      i += 1;
      vector_push(&tokens, &t);
    }
    else {
      assert(false);
    }
  }

  return tokens;
}
