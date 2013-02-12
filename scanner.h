// $Id: scanner.h 565 2011-03-09 01:07:22Z phf $

#ifndef _SCANNER_H
#define _SCANNER_H

#include "tokens.h"

#include "strings.h"
#include "vectors.h"

// Convert string source into a vector of tokens.
vector_t scan(string_t *source);

#endif /* _SCANNER_H */
