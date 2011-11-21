CFLAGS:=--std=c99 -finput-charset=UTF-8

all: alite

.PHONY: clean
clean:
	rm y.tab.c *.o alite

alite: y.tab.c lex.c
	$(CC) $(CFLAGS) -o $@ $^

y.tab.c y.tab.h: alite.y
	$(YACC) -d -y $^
