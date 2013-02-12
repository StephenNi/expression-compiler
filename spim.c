// $Id: spim.c 637 2013-02-11 00:09:36Z phf $

#include "spim.h"

#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define LEN 32

static char *mapping[] = {
  [PLUS] = "add",
  [MINUS] = "sub",
  [TIMES] = "mul",
  [SLASH] = "div",
};

static void label(string_t *buffer, const char *lab) {
  string_append_chars(buffer, lab);
  string_append_chars(buffer, ":\n");
}

static void instruction(string_t *buffer, const char *inst) {
  string_append_char(buffer, '\t');
  string_append_chars(buffer, inst);
  string_append_char(buffer, '\n');
}

// For MIPS the $sp points to the top element, so we have
// to adjust $sp *before* storing but *after* loading.

static void push(string_t *buffer, const char *reg) {
  int res;
  char inst[LEN] = "";
  assert(strlen(reg) == 3);
  instruction(buffer, "addi $sp, $sp, -4");
  res = snprintf(inst, LEN, "sw %s, ($sp)", reg);
  assert(res < LEN);
  instruction(buffer, inst);
}

static void pop(string_t *buffer, const char *reg) {
  int res;
  char inst[LEN] = "";
  assert(strlen(reg) == 3);
  res = snprintf(inst, LEN, "lw %s, ($sp)", reg);
  assert(res < LEN);
  instruction(buffer, inst);
  instruction(buffer, "addi $sp, $sp, 4");
}

static void load(string_t *buffer, int val, const char *reg) {
  int res;
  char inst[LEN] = "";
  assert(strlen(reg) == 3);
  res = snprintf(inst, LEN, "li %s, %d", reg, val);
  assert(res < LEN);
  instruction(buffer, inst);
  push(buffer, reg);
}

static bool operator(node_kind_t kind) {
  // requires kinds to be ordered appropriately
  return (PLUS <= kind && kind <= SLASH);
}

static void operation(string_t *buffer, node_kind_t kind) {
  int res;
  char inst[LEN] = "";
  assert(operator(kind));
  pop(buffer, "$s1");
  pop(buffer, "$s0");
  res = snprintf(inst, LEN, "%s $s0, $s0, $s1", mapping[kind]);
  assert(res < LEN);
  instruction(buffer, inst);
  push(buffer, "$s0");
}

static void prologue(string_t *buffer) {
  instruction(buffer, ".data");
  label(buffer, "newline");
  instruction(buffer, ".asciiz \"\\n\"");
  instruction(buffer, ".text");
  label(buffer, "main");
}

static void epilogue(string_t *buffer) {
  label(buffer, "print");
  pop(buffer, "$a0");
  instruction(buffer, "li $v0, 1");
  instruction(buffer, "syscall");
  instruction(buffer, "la $a0, newline");
  instruction(buffer, "li $v0, 4");
  instruction(buffer, "syscall");
  label(buffer, "exit");
  instruction(buffer, "li $v0, 10");
  instruction(buffer, "syscall");
  instruction(buffer, ".end");
}

static void recurse(const node_t *ast, string_t *buffer) {
  if (ast->kind == INTEGER) {
    load(buffer, ast->value, "$s0");
  }
  else if (operator(ast->kind)) {
    recurse(ast->left, buffer);
    recurse(ast->right, buffer);
    operation(buffer, ast->kind);
  }
  else {
    // invalid kind in abstract syntax tree
    assert(0);
  }
}

void generate(const node_t *ast, string_t *buffer) {
  prologue(buffer);
  recurse(ast, buffer);
  epilogue(buffer);
}
