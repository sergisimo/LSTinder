all: Morty

H=./HEADERS/
S=./SOURCES/

main.o: $Smain.c $Hconsole.h
	gcc $Smain.c -c -Wall -Wextra

console.o: $Sconsole.c $Hio.h
	gcc $Sconsole.c -c -Wall -Wextra

io.o: $Sio.c $Htipus.h
	gcc $Sio.c -c -Wall -Wextra

Morty: main.o console.o io.o
	gcc main.o console.o io.o -o Morty -Wall -Wextra

clean:
	rm *.o Morty
