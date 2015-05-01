input=right1.inp
debug=-dp
copt=-std=c11 #-Wpedantic -Wall -Wextra -Wold-style-definition -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-field-initializers

run: proj
	 ./proj < $(input) 2>&1 | tee out/parse

proj: driver.c proj.y proj.l 
	flex proj.l 2>&1 | tee out/flex
	bison proj.y --debug --verbose 2>&1 | tee out/bison
	gcc $(copt) -D DEBUG -ggdb -o proj -I. lib/string.c lib/list.c lib/type.c lib/var.c lib/fun.c lib/scope.c lib/typecheck.c driver.c proj.tab.c 2>&1 | tee out/gcc

clean: 
	rm proj lex.yy.c proj.tab.c