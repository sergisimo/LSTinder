/********************************************************************
*
* @Arxiu : client.c
* @Finalitat : Implementar nova conexio amb LSTinder
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/client.h"

void CLIENT_connect (Configuration configuration) {

  char tramaCon[115] = CLIENT_CONNECTION_REQUEST;
  char * type;

  int i;

  for(i = 5; i < 115; i++) tramaCon[i]='\0';

  configuration.clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (configuration.clientSocketFD < 0) {
    SINGNALS_programExit(-1, CLIENT_KO_CONNECTION_MESSAGE);
  } else {

    if (connect(configuration.clientSocketFD, (void *) &(configuration.clientConf), sizeof(configuration.clientConf)) < 0) {
      SINGNALS_programExit(-1, CLIENT_KO_CONNECTION_MESSAGE);
    } else {

      write(configuration.clientSocketFD, tramaCon, 115);
      read(configuration.clientSocketFD, tramaCon, 115);

      type = SERVER_substring(tramaCon, 0, 4);
      if (!strcmp(type, CLIENT_CONECTION_OK_RESPONSE)){

        write (1, CLIENT_OK_CONNECTION_MESSAGE, strlen(CLIENT_OK_CONNECTION_MESSAGE));
      }else{

        SINGNALS_programExit(-1, CLIENT_KO_CONNECTION_MESSAGE); //Control d'errors
      }
    }
  }
}
