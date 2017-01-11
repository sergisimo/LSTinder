all: Morty

H=./HEADERS/
S=./SOURCES/
OBJ=main.o console.o conection.o io.o signals.o command.o
FLAGS=-Wall -Wextra -lpthread

main.o: $Smain.c $Hconsole.h $Hconection.h
	gcc $Smain.c -c $(FLAGS)

console.o: $Sconsole.c $Hio.h $Hconection.h
	gcc $Sconsole.c -c $(FLAGS)

conection.o: $Sconection.c $Hcommand.h $Hio.h $Hconsole.h
	gcc $Sconection.c -c $(FLAGS)

io.o: $Sio.c $Hsignals.h
	gcc $Sio.c -c $(FLAGS)

signals.o: $Ssignals.c $Htipus.h $Hconection.h
	gcc $Ssignals.c -c $(FLAGS)

command.o: $Scommand.c $Hsignals.h
	gcc $Scommand.c -c $(FLAGS)

Morty: $(OBJ)
	gcc $(OBJ) -o Morty $(FLAGS)

clean:
	rm *.o Morty
