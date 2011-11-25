<$PLAN9/src/mkhdr

TARG=alite
YFILES=alite.y
HFILES=ast.h eval.h pprint.h symtable.h util.h y.tab.h
OFILES=y.tab.$O lex.$O util.$O ast.$O pprint.$O eval.$O symtable.$O
CFLAGS="-std=c99 -fms-extensions"

<$PLAN9/src/mkone
