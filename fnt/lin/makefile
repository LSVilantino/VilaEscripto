projecto = lsve

all:
	gcc -std=c99 -g *.c -o $(projecto)

r:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(projecto) "teste.lsve" "teste2.lsve"
