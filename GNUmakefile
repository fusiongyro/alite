CFLAGS:=--std=c99 -finput-charset=UTF-8

all: alite

.PHONY: clean
clean:
	rm y.tab.c y.tab.h *.o alite

alite: y.tab.c lex.c util.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

util.o: util.h util.c

y.tab.c y.tab.h: alite.y
	$(YACC) -d $^
