all: Morty

H=./HEADERS/
S=./SOURCES/

main.o: $Smain.c $Hconsole.h
	gcc $Smain.c -c -Wall -Wextra

console.o: $Sconsole.c $Hio.h
	gcc $Sconsole.c -c -Wall -Wextra

io.o: $Sio.c $Hsignals.h
	gcc $Sio.c -c -Wall -Wextra

signals.o: $Ssignals.c $Htipus.h
	gcc $Ssignals.c -c -Wall -Wextra

Morty: main.o console.o io.o signals.o
	gcc main.o console.o io.o signals.o -o Morty -Wall -Wextra

clean:
	rm *.o Morty
