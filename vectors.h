// $Id: vectors.h 565 2011-03-09 01:07:22Z phf $
//
// A simple vector abstraction, essentially a dynamically growing
// array based on amortized doubling. Error handling is done with
// assert()s, so make sure you know what you're doing. :-)
//
// Uses a malloc()/free() scheme instead of mmap()/munmap() stuff.
// Since we want to be generic without having generics we must use
// void* for elements. A wrapper, customized for character strings
// for example, can hide this behind a nicer interface. Don't want
// to copy elements in and out? Use a vector of pointers!
//
// Copyright (c) 2007-2010 by Peter H. Froehlich <phf@acm.org>.
// All rights reserved.

#ifndef _VECTORS_H
#define _VECTORS_H

#include <stdlib.h>

// Representation of a vector
typedef struct {
  size_t element; // size (in bytes) of one element
  size_t length; // current length (elements 0 to length-1 are valid)
  size_t capacity; // current capacity (elements 0 to capacity-1 are backed)
  char *data; // capacity * element bytes of memory
} vector_t;

// Create empty vector of default capacity for elements
// of given size (in bytes, from sizeof).
void vector_new(vector_t *v, size_t size);

// Create empty vector of given capacity for elements
// of given size (in bytes, from sizeof).
void vector_new_capacity(vector_t *v, size_t capacity, size_t size);

// Delete vector, freeing all memory we ever allocated
// for it.
void vector_delete(/*@only@*/ vector_t *v);

// Append an element, grow vector if necessary; assumes
// element has proper size.
void vector_push(vector_t *v, const void *element);

// Remove last element we appended; assumes
// vector is not empty.
void vector_pop(vector_t *v);

// Get element by index, copying into buffer; assumes
// buffer has proper size.
void vector_get(const vector_t *v, size_t index, void *buffer);

// Put element by index, copying from buffer; assume
// buffer has proper size.
void vector_put(vector_t *v, size_t index, const void *buffer);

// Dump vector state to stdout (for debugging).
void vector_dump(const vector_t *v);

#endif /* _VECTORS_H */
