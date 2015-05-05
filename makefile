CC=gcc
CFLAGS=-g -c
INCLUDES=-I ./include/
LEX=flex
LFLAGS=
YACC=bison
YFLAGS=-dv
#File extension
EXT=1

all: valPropFsmd

#creates the executable file
valPropFsmd : valPropCode.o lva.o normalization.o fsmdCode.o fsmda.tab.o lex.yy.o
	$(CC) -g -o ./bin/valPropFsmd ./obj/*.o


#creates the object files
fsmda.tab.o : parser
	$(CC) $(CFLAGS) $(INCLUDES) ./src/fsmda.tab.c -o ./obj/fsmda.tab.o

lex.yy.o : parser
	$(CC) $(CFLAGS) $(INCLUDES) ./src/lex.yy.c -o ./obj/lex.yy.o

valPropCode.o :
	$(CC) $(CFLAGS) -Wall $(INCLUDES) ./src/valPropCode.c -o ./obj/valPropCode.o

lva.o :
	$(CC) $(CFLAGS) -Wall $(INCLUDES) ./src/lva.c -o ./obj/lva.o

normalization.o :
	$(CC) $(CFLAGS) -Wall $(INCLUDES) ./src/normalization.c -o ./obj/normalization.o

fsmdCode.o :
	$(CC) $(CFLAGS) $(INCLUDES) ./src/fsmdCode.c -o ./obj/fsmdCode.o



#calls the parser
parser : lexer
	$(YACC) $(YFLAGS) ./src/fsmda.y
	mv ./fsmda.tab.h ./include/fsmda.tab.h
	mv ./fsmda.tab.c ./src/fsmda.tab.c
	mv ./fsmda.output ./obj/fsmda.output

#calls the lexer
lexer :  
	$(LEX) $(LFLAGS) ./src/fsmda.lex
	mv ./lex.yy.c ./src/lex.yy.c



clean :
	rm -rf ./obj/*.o
	rm -rf ./obj/*.output
	rm -rf ./include/*.tab.h
	rm -rf ./bin/valPropFsmd
	rm -rf ./src/*.tab.c
	rm -rf ./src/lex.yy.c


#####################

