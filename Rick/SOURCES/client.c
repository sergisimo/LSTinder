/********************************************************************
*
* @Arxiu : client.c
* @Finalitat : Implementar nova conexio amb LSTinder
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/client.h"

void CLIENT_connect (Configuration * configuration) {

  Command command;
  CommandType commandType;

  COMMAND_create(command);
  COMMAND_setType(command, CLIENT_CONNECTION_REQUEST);

  configuration->clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (configuration->clientSocketFD < 0) {
    SINGNALS_programExit(-1, CLIENT_KO_CONNECTION_MESSAGE);
  } else {

    if (connect(configuration->clientSocketFD, (void *) &(configuration->clientConf), sizeof(configuration->clientConf)) < 0) {
      SINGNALS_programExit(-1, CLIENT_KO_CONNECTION_MESSAGE);
    } else {

      write(configuration->clientSocketFD, command, COMMAND_SIZE);
      read(configuration->clientSocketFD, command, COMMAND_SIZE);

      commandType = COMMAND_getType(command);

      if (commandType == LSTinderConnectionOK) {

        write (1, CLIENT_OK_CONNECTION_MESSAGE, strlen(CLIENT_OK_CONNECTION_MESSAGE));
      }

      if (commandType == LSTinderConnectionKO) {

        SINGNALS_programExit(-1, CLIENT_KO_CONNECTION_MESSAGE); //Control d'errors
      }
    }
  }
}
