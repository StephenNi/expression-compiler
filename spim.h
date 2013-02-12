// $Id: spim.h 565 2011-03-09 01:07:22Z phf $

#ifndef _SPIM_H
#define _SPIM_H

#include "strings.h"
#include "nodes.h"

// Generate SPIM code from abstract syntax tree.
void generate(const node_t *ast, string_t *buffer);

#endif /* _SPIM_H */
