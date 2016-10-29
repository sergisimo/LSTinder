/* **********************************************
 *
 * @Arxiu : io.c
 * @Finalitat : Implementa funcions d'entrada i sortida.
 * @Autor : Sergi Simó Bosquet - ls30685 & Esteve Genovard Ferriol - ls30742
 * @Data : 2016
 *
 ************************************************/

#include "io.h"

/* Sense espais al davant i '\0' al final*/
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
  cadena[length-1] = '\0';

	return cadena;
}

Configuration IO_llegeixFitxerConfiguration() {

	int f;
	Configuration configuration;

	f = open(FCONF, O_RDONLY);
  if (f < 0) {
    write (2, "Error! El fitxer de configuracio no s'ha pogut obrir.", strlen("Error! El fitxer de configuracio no s'ha pogut obrir."));
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

	f = open(FINF, O_RDONLY);
	if (f < 0) {
		write (2, "Error! El fitxer de configuracio no s'ha pogut obrir.", strlen("Error! El fitxer de configuracio no s'ha pogut obrir."));
	} else {
		information.name = IO_llegirLinia(f);
		information.age = atoi(IO_llegirLinia(f));
		information.description = IO_llegirLinia(f);
	}

	close(f);

	return information;
}
