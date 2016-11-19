all: Morty

H=./HEADERS/
S=./SOURCES/

main.o: $Smain.c $Hconsole.h $Hconection.h
	gcc $Smain.c -c -Wall -Wextra -lpthread

console.o: $Sconsole.c $Hio.h
	gcc $Sconsole.c -c -Wall -Wextra -lpthread

conection.o: $Sconection.c $Htipus.h
	gcc $Sconection.c -c -Wall -Wextra -lpthread

io.o: $Sio.c $Hsignals.h
	gcc $Sio.c -c -Wall -Wextra -lpthread

signals.o: $Ssignals.c $Htipus.h
	gcc $Ssignals.c -c -Wall -Wextra -lpthread

Morty: main.o console.o conection.o io.o signals.o
	gcc main.o console.o conection.o io.o signals.o -o Morty -Wall -Wextra -lpthread

clean:
	rm *.o Morty
