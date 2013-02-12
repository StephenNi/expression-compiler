// $Id: parser.c 565 2011-03-09 01:07:22Z phf $

#include "parser.h"

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

// Tokens to parse through.
static vector_t *tokens;
// How many tokens?
static size_t length;
// Current position in tokens?
static size_t position;
// Current token we're processing.
static token_t current;

static bool valid(void) {
  return position < length;
}

static void next(void) {
  if (valid()) {
    vector_get(tokens, position, &current);
    position += 1;
  }
}

static node_t *Expression(void);

static node_t *Factor(void) {
  node_t *expr = NULL;

  switch (current.kind) {
    case OPEN:
      next();
      expr = Expression();
      if (current.kind != CLOSE) {
        puts(") expected!");
        exit(1);
      }
      else {
        next();
      }
      break;
    case INTEGER:
      expr = node_new(INTEGER);
      expr->value = current.value;
      next();
      break;
    default:
      puts("( or integer expected!");
      exit(1);
      break;
  }

  return expr;
}

static node_t *Term(void) {
  node_t *left = Factor();
  node_t *right, *new;
  while (current.kind == TIMES || current.kind == SLASH) {
    node_kind_t op = current.kind;
    next();
    right = Factor();
    new = node_new(op);
    new->left = left;
    new->right = right;
    left = new;
  }
  return left;
}

static node_t *Expression(void) {
  node_t *left = Term();
  node_t *right, *new;
  while (current.kind == PLUS || current.kind == MINUS) {
    node_kind_t op = current.kind;
    next();
    right = Term();
    new = node_new(op);
    new->left = left;
    new->right = right;
    left = new;
  }
  return left;
}

node_t *parse(vector_t *ts) {
  tokens = ts;
  length = ts->length;
  position = 0;
  next();
  return Expression();
}

