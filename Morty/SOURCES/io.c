/* **********************************************
 *
 * @Arxiu : io.c
 * @Finalitat : Implementa funcions d'entrada i sortida del programa LSTinder.
 * @Autor : Sergi Simó Bosquet - ls30685 & Esteve Genovard Ferriol - ls30742
 * @Data : 2016
 *
 ************************************************/

#include "../HEADERS/io.h"

char * IO_readKeyboard () {

	char * frase;
	char c;
	int i = 0;

	frase = (char *) malloc(sizeof(char));
	read(0, &c, 1);
	while (c == ' '){
		read (0, &c,1);
	}
	while (c != '\n') {
		frase[i] = c;
		i++;
		frase = (char*)realloc(frase, sizeof(char)*(i + 1));
		read(0, &c, 1);
	}
	frase[i] = '\0';

	return frase;
}

char * IO_llegirLinia (int f) {

	char aux;
	char * cadena;

	int length = 0;
  cadena = (char *) malloc(sizeof(char));

  do {
    read(f, &aux, 1);
    cadena[length] = aux;
		length++;
		cadena = (char*)realloc(cadena, sizeof(char)*(length + 1));
  }while (aux != '\n');
  cadena[length-2] = '\0';

	return cadena;
}

Configuration IO_llegeixFitxerConfiguration() {

	int f;
	Configuration configuration;

	f = open(IO_FCONF, O_RDONLY);
  if (f < 0) {
    SINGNALS_programExit(-1, IO_OPEN_CONFIGURATION_FILE_ERROR);
  } else {
		configuration.userName = IO_llegirLinia(f);
		configuration.addr = IO_llegirLinia(f);
		configuration.sin_port = atoi(IO_llegirLinia(f));
	}

	close(f);

	return configuration;
}

Information IO_llegeixFitxerInformation(){
	int f;
	Information information;

	f = open(IO_FINF, O_RDONLY);
	if (f < 0) {
		SINGNALS_programExit(-1, IO_OPEN_CONFIGURATION_FILE_ERROR);
	} else {
		information.name = IO_llegirLinia(f);
		information.age = atoi(IO_llegirLinia(f));
		information.description = IO_llegirLinia(f);
	}

	close(f);

	return information;
}
