/********************************************************************
*
* @Arxiu : main.c
* @Finalitat : Implementar el procediment principal del programa Rick.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 de Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/client.h"

int main () {

  SIGNALS_initializeSignals();

  Configuration conf = IO_readConfigurationFile();

  CLIENT_connect(conf);

  SERVER_connect(&conf);

  SERVER_listenClients(conf);

  return 0;
}
