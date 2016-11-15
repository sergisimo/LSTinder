/********************************************************************
*
* @Arxiu : io.c
* @Finalitat : Implementar totes les funcions pel que fa l'entrada i sortida de fitxers.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 de Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/io.h"

char * IO_readLine (int f) {

	char aux;
	char * cadena;

	int length = 0;

  cadena = (char *) malloc(sizeof(char));
	if (cadena == NULL); //control d'errors.

  do {

    read(f, &aux, 1);
    cadena[length] = aux;
		length++;
		cadena = (char*)realloc(cadena, sizeof(char)*(length + 1));
		if (cadena == NULL); //control d'errors.
  }while (aux != '\n');
  cadena[length-1] = '\0';

	return cadena;
}

Configuration IO_readConfigurationFile() {

	int f;

	Configuration configuration;

  char * aux;

	f = open(IO_FCONF, O_RDONLY);
  if (f < 0) {
		//Control d'errors
  } else {

		bzero(&configuration.serverConf, sizeof(configuration.serverConf));
		memset(&configuration.clientConf, 0, sizeof(configuration.serverConf));

		configuration.serverConf.sin_family = configuration.clientConf.sin_family = AF_INET;

    aux = IO_readLine(f);
		configuration.mortyRefresh = atoi(aux);
    free(aux);

    aux = IO_readLine(f);
		configuration.serverConf.sin_port = htons(atoi(aux));
    free(aux);

    aux = IO_readLine(f);
		inet_aton(aux, &configuration.serverConf.sin_addr);
    inet_aton(aux, &configuration.clientConf.sin_addr);
    free(aux);

    aux = IO_readLine(f);
    configuration.clientConf.sin_port = htons(atoi(aux));
    free(aux);
	}

	close(f);

	return configuration;
}
