CFLAGS:=--std=c99 -finput-charset=UTF-8

all: alite

.PHONY: clean
clean:
	rm -f y.tab.c y.tab.h *.o alite

alite: y.tab.c lex.c util.o ast.o pprint.o eval.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

util.o: util.h util.c
ast.o: y.tab.h ast.h
eval.o: eval.c eval.h ast.h
pprint.o: pprint.c pprint.h ast.h

y.tab.c y.tab.h: alite.y
	$(YACC) -d $^
