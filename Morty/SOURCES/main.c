#include "../HEADERS/console.h"
#include "../HEADERS/conection.h"

int main () {

	int socket;
	struct sockaddr_in s_addr;

	SIGNALS_initializeSignals();

	configuration = IO_llegeixFitxerConfiguration();
	information = IO_llegeixFitxerInformation();

	s_addr = CONECTION_preparation (configuration);
	socket = CONECTION_stablishConection (s_addr);
	CONECTION_newConection(configuration, information, socket);
	CONECTION_desconection(configuration, socket);

	pthread_t threads;
	pthread_create(&threads, NULL, CONECTION_listenServer, &socket);

	CONSOLE_start();


	close(socket);

	return 0;
}
