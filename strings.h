// $Id: strings.h 565 2011-03-09 01:07:22Z phf $
//
// Simple string representation based on vectors. One ugly
// wart is that we have to maintain an explicit NUL at the
// end of the string to reuse the vector code verbatim.
//
// Copyright (c) 2010 by Peter H. Froehlich <phf@acm.org>.
// All rights reserved.

#ifndef _STRINGS_H
#define _STRINGS_H

#include "vectors.h"

// Representation of a string
typedef vector_t string_t;

// Create empty new string of default capacity.
void string_new(string_t *s);

// Create a new string from the given characters.
void string_str(string_t *s, const char *chars);

// Delete string, freeing all memory we allocated for it.
void string_delete(/*@only@*/ string_t *s);

// Append a character, grow the string if necessary.
void string_append_char(string_t *s, char c);

// Append a C string, grow the string if necessary.
void string_append_chars(string_t *s, const char *c);

// Dump string state to stdout (for debugging).
void string_dump(const string_t *s);

// Compare two strings, return < 0 if s < t, == 0 if s == t, > 0 if s > t.
int string_compare(const string_t *s, const string_t *t);

#endif /* _STRINGS_H */
