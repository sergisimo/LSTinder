#include "../HEADERS/console.h"
#include "../HEADERS/conection.h"

Configuration configuration;

int main () {
	int socket;
	struct sockaddr_in s_addr;

	SIGNALS_initializeSignals();
	IO_llegeixFitxerConfiguration();
	information = IO_llegeixFitxerInformation();

	s_addr = CONECTION_preparation (configuration);
	socket = CONECTION_stablishConection (s_addr);
	configuration.sock = socket;
	CONECTION_newConection(configuration, information, socket);

	CONSOLE_start(configuration, socket);

	return 0;
}
