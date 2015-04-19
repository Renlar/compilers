##Compilers Semester Project

###Coding Guidelines
####Functions
1. Fuctions which will be used outside of the current file should be declared in a header file.
2. No functions should be implemented in header files except accessors.
3. Function names should describe the purpose of the method and prefer clairity over conciseness.
4. Functions which are associated with a struct should be prefixed with the struct name and declared in the same header file as the struct.
5. No data element should be directly accessed outside of the file pair it is defined in, instead mutators and accessors (if necessary) should be defined.
6. Every function ment for use outside of the current file pair should have a documentation block consisting of the following:
  * An overall description of the method. This is not required if the argument and return descriptions make the purpose and use of the method clear.
  * A short description of each return values and argument.
  * Documentation layout:
    * *Description of the method*
    * @arg *\<argument name\>* *Description of the argument*
    * @return *Description of return value*
7. Functions should be less than 20 lines in length to prevent bugs and reduce debugging time.
8. Functions should return values they generate through the standard c return statement.
9. Functionss which are not intended for use outside of the current file pair should be predefined in a block marked as private at the beginning of the c file instead of the h file.

####Arguemnts
1. Avoid passing function pointers as arguments, unless it greately increases the usability or readability of the code.
2. The number of arguments to functions should be 4 or fewer, if greator than 7 the design needs to be rethought.
3. Arguments should not be used to return results which are generated in the function.
4. Any arguements used to return results directly through setting a pointer or indirectly through modification of the input values should come first in the argument list.

####Pointers
1. Double pointers and greator are avoided as much as possible.  If they must be used they should be hidden behind mutators and accessors.
2. Pointers are treated as references whenever possible.
3. Pointer arithmetic should be avoided.  If it is used it should be peformed in a "library" file, protected by mutators and accessors.

####Naming
1. Function names should be in lower\_snake\_case.
2. Variable names should be in lowerCammelCase.
3. Struct names should be in Upper\_Snake\_Case
4. The typedef of a pointer to a struct should be in UpperCammelCase.
5. The size constant for structs should be in all lower case beginning with 'sizeof\_' followed by the struct pointer typedef name in all lower case, e.g. 'packingstruct'

####Structs
1. A typedef should be created for each struct which is a pointer to the struct.
2. A constant containing the size of the struct should be defined in all lowercase prefixed by 'sizeof\_'.
3. Struct data elements should be declared in the order from most to least frequently accessed


###Part 1
Implement a parser for a subset of ml.
Code files:
* Makefile
* proj.l
* proj.y
Test files:
* right1.inp
* wrong1.inp
* test_cases/right.inp
* test_cases/right1.inp
* test_cases/right2.inp


###Part 2
Implement type checking for the grammar parsed in part 1.
Code files:
* lib/*
Test files:
* Same as part 1


###Part 3
Generate an AST using the grammar from part 1.


###Part 4

