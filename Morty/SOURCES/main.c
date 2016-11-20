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

	CONSOLE_start();

	CONECTION_desconection(configuration, socket);
	close(socket);

	return 0;
}
