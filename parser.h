// $Id: parser.h 565 2011-03-09 01:07:22Z phf $

#ifndef _PARSER_H
#define _PARSER_H

#include "vectors.h"
#include "nodes.h"

// Convert vector of tokens into abstract syntax tree.
node_t *parse(vector_t *tokens);

#endif /* _PARSER_H */
