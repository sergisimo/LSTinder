all: Rick

H=./HEADERS/
S=./SOURCES/
OBJ=main.o io.o server.o llista.o signals.o client.o command.o seenList.o
FLAGS=-Wall -Wextra -lpthread

main.o: $Smain.c $Hclient.h $Hserver.h
	gcc $Smain.c -c $(FLAGS)

io.o: $Sio.c $Hsignals.h
	gcc $Sio.c -c $(FLAGS)

server.o: $Sserver.c $Hllista.h $HseenList.h $Hio.h $Hcommand.h $Hclient.h
	gcc $Sserver.c -c $(FLAGS)

llista.o: $Sllista.c $HseenList.h
	gcc $Sllista.c -c $(FLAGS)

signals.o: $Ssignals.c $Htipus.h
	gcc $Ssignals.c -c $(FLAGS)

client.o: $Sclient.c $Hcommand.h $Hsignals.h $Hserver.h
	gcc $Sclient.c -c $(FLAGS)

command.o: $Scommand.c $Hsignals.h
	gcc $Scommand.c -c $(FLAGS)

seenList.o: $SseenList.c $Htipus.h
	gcc $SseenList.c -c $(FLAGS)

Rick: $(OBJ)
	gcc $(OBJ) -o Rick $(FLAGS)

clean:
	rm *.o Rick
