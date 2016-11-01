#include "../HEADERS/console.h"

int main () {

	SIGNALS_initializeSignals();
	
	configuration = IO_llegeixFitxerConfiguration();
	information = IO_llegeixFitxerInformation();

	CONSOLE_start();

	return 0;
}
