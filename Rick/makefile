all: Rick

H=./HEADERS/
S=./SOURCES/
OBJ=main.o io.o server.o llista.o signals.o client.o
FLAGS=-Wall -Wextra -lpthread

main.o: $Smain.c $Hclient.h
	gcc $Smain.c -c $(FLAGS)

io.o: $Sio.c $Hsignals.h
	gcc $Sio.c -c $(FLAGS)

server.o: $Sserver.c $Hllista.h $Hio.h
	gcc $Sserver.c -c $(FLAGS)

llista.o: $Sllista.c $Hsignals.h
	gcc $Sllista.c -c $(FLAGS)

signals.o: $Ssignals.c $Htipus.h
	gcc $Ssignals.c -c $(FLAGS)

client.o: $Sclient.c $Hserver.h
	gcc $Sclient.c -c $(FLAGS)

Rick: $(OBJ)
	gcc $(OBJ) -o Rick $(FLAGS)

clean:
	rm *.o Rick
