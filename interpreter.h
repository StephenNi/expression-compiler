// $Id: interpreter.h 565 2011-03-09 01:07:22Z phf $

#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "nodes.h"

// Evaluate abstract syntax tree.
int eval(const node_t *ast);

#endif /* _INTERPRETER_H */
