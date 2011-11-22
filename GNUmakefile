CFLAGS:=--std=c99 -finput-charset=UTF-8

all: alite

.PHONY: clean
clean:
	rm -f y.tab.c y.tab.h *.o alite

alite: y.tab.c lex.o util.o ast.o pprint.o eval.o symtable.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

ast.o: ast.c y.tab.h ast.h
eval.o: eval.c pprint.h ast.h eval.h symtable.h
lex.o: lex.c y.tab.h
pprint.o: pprint.c pprint.h ast.h
symtable.o: symtable.c symtable.h
util.o: util.c util.h
y.tab.o: y.tab.c util.h ast.h eval.h symtable.h

y.tab.c y.tab.h: alite.y
	$(YACC) -d $^
