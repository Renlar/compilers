input=right1.inp
debug=-dp
copt=-std=c11

run: proj
	 ./proj < $(input)

proj: driver.c proj.y proj.l 
	flex proj.l
	bison proj.y
	gcc $(copt) -o proj -I. driver.c proj.tab.c

clean: 
	rm proj lex.yy.c proj.tab.c
