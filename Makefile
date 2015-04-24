input=right1.inp
debug=-dp
copt=-std=c11 #-Wpedantic -Wall -Wextra -Wold-style-definition -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-field-initializers

run: proj
	 ./proj < $(input)

proj: driver.c proj.y proj.l 
	flex proj.l
	bison proj.y --debug --verbose
	gcc $(copt) -o proj -I. lib/string.c lib/list.c lib/type.c lib/var.c lib/fun.c lib/scope.c lib/typecheck.c driver.c proj.tab.c

clean: 
	rm proj lex.yy.c proj.tab.c
