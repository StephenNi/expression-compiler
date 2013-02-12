# $Id: Makefile 639 2013-02-11 00:16:04Z phf $
CFLAGS=-pedantic -Wall -Wextra -std=c99 -O0 -g #-D_FORTIFY_SOURCE=2 #-fmudflap
#LDFLAGS=-fmudflap
CC=gcc

ALL=test_vectors test_strings test_tokens test_scanner test_nodes test_parser test_interpreter test_spim main

all:		$(ALL)

test_vectors:	vectors.o test_vectors.o
test_vectors.o:	vectors.h test_vectors.c
vectors.o:	vectors.h vectors.c

test_strings:	vectors.o strings.o test_strings.o
test_strings.o:	vectors.h strings.h test_strings.c
strings.o:	vectors.h strings.h strings.c

test_tokens:	tokens.o test_tokens.o
test_tokens.o:	tokens.h test_tokens.c
tokens.o:	tokens.h tokens.c

test_scanner:	vectors.o strings.o tokens.o scanner.o test_scanner.o
test_scanner.o:	vectors.h strings.h tokens.h scanner.h test_scanner.c
scanner.o:	vectors.h strings.h tokens.h scanner.h scanner.c

test_nodes:	nodes.o test_nodes.o
test_nodes.o:	tokens.h nodes.h test_nodes.c
nodes.o:	tokens.h nodes.h nodes.c

test_parser:	vectors.o strings.o tokens.o scanner.o nodes.o parser.o test_parser.o
test_parser.o:	vectors.h strings.h tokens.h scanner.h nodes.h parser.h test_parser.c
parser.o:	vectors.h strings.h tokens.h nodes.h parser.h parser.c

test_interpreter:	vectors.o strings.o tokens.o scanner.o nodes.o parser.o interpreter.o test_interpreter.o
test_interpreter.o:	vectors.h strings.h tokens.h scanner.h nodes.h parser.h interpreter.h test_interpreter.c
interpreter.o:		vectors.h strings.h tokens.h nodes.h interpreter.h interpreter.c

test_spim:	vectors.o strings.o tokens.o scanner.o nodes.o parser.o spim.o test_spim.o
test_spim.o:	vectors.h strings.h tokens.h scanner.h nodes.h parser.h spim.h test_spim.c
spim.o:		vectors.h strings.h tokens.h nodes.h spim.h spim.c

main:		vectors.o strings.o tokens.o scanner.o nodes.o parser.o interpreter.o spim.o main.o
main.o:		vectors.h strings.h tokens.h scanner.h nodes.h parser.h interpreter.h spim.h main.c

clean:
	rm -rf *.o $(ALL) tutorial-c.tar.gz
splint:
	splint *.c
dist:
	tar zcvf tutorial-c.tar.gz *.h *.c Makefile README TODO
