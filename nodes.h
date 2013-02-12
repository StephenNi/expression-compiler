// $Id: nodes.h 565 2011-03-09 01:07:22Z phf $

#ifndef _NODES_H
#define _NODES_H

#include "tokens.h"

// Node kinds
// TODO: smaller enum to avoid OPEN and CLOSE?
typedef token_kind_t node_kind_t;

// Representation of an AST node
typedef struct node {
  node_kind_t kind;
  int value;
  struct node *left;
  struct node *right;
} node_t;

// Create a new node of the given kind; all other fields
// are zeroed out.
node_t *node_new(node_kind_t kind);

// Delete a node and (recursively) all its children.
// TODO: should this be node_destroy or node_obliterate?
void node_delete(node_t *node);

// Dump node to stdout (for debugging).
void node_dump(const node_t *t);

#endif
