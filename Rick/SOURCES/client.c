/********************************************************************
*
* @Arxiu : client.c
* @Finalitat : Implementar nova conexio amb LSTinder
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/client.h"

void* CLIENT_updateThread(void * segonsPointer) {

  int segons = *((int *) segonsPointer);
  update = 0;

  alarm(10);

  while (!update) pause();
  CLIENT_updateList();
  update = 0;
  alarm(segons);

  while (1) {

    while(!update) pause();
    CLIENT_updateList();
    update = 0;
    alarm(segons);
  }
}

void CLIENT_updateList() {

  Command command;
  CommandType commandType;
  char aux[50];
  int final = 0, total = 0;
  Client client;

  COMMAND_create(command);
  COMMAND_setType(command, COMMAND_TYPE_LSTINDER_USER_SEND);
  COMMAND_setInfo(command, COMMAND_INFO_LSTINDER_USER);

  pthread_mutex_lock(&semaforLlistaMortys);
  LLISTA_destrueix(&llistaMortys);
  llistaMortys = LLISTA_crea();
  pthread_mutex_unlock(&semaforLlistaMortys);

  write(1, CLIENT_SAVING_INFORMATION_MESSAGE, strlen(CLIENT_SAVING_INFORMATION_MESSAGE));
  write(conf.clientSocketFD, command, COMMAND_SIZE);

  while (!final) {

    read(conf.clientSocketFD, command, COMMAND_SIZE);
    commandType = COMMAND_getType(command);

    if (commandType == LSTinderUser) {

      client.info.name = COMMAND_getData(command, 15, 24);
      client.nickName = COMMAND_getData(command, 25, 39);
      client.info.age = atoi(COMMAND_getData(command, 40, 41));
      client.info.description = COMMAND_getData(command, 42, 114);
      total++;

      sprintf(aux, "Morty: %s\n", client.nickName);
      write(1, aux, strlen(aux));

      pthread_mutex_lock(&semaforLlistaMortys);
      LLISTA_insereix(&llistaMortys, client);
      pthread_mutex_unlock(&semaforLlistaMortys);
    } else {

      final = 1;
      if (!total) write(1, CLIENT_NO_MORTY_AVIABLE, strlen(CLIENT_NO_MORTY_AVIABLE));
    }
  }
}

void CLIENT_connect (Configuration * configuration) {

  Command command;
  CommandType commandType;

  COMMAND_create(command);
  COMMAND_setType(command, CLIENT_CONNECTION_REQUEST);
  llistaMortys = LLISTA_crea();

  configuration->clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (configuration->clientSocketFD < 0) {
    SINGNALS_programExit(-2, CLIENT_KO_CONNECTION_MESSAGE);
  } else {

    if (connect(configuration->clientSocketFD, (void *) &(configuration->clientConf), sizeof(configuration->clientConf)) < 0) {
      SINGNALS_programExit(-2, CLIENT_KO_CONNECTION_MESSAGE);
    } else {

      write(configuration->clientSocketFD, command, COMMAND_SIZE);
      read(configuration->clientSocketFD, command, COMMAND_SIZE);

      commandType = COMMAND_getType(command);

      if (commandType == LSTinderConnectionOK) {

        write (1, CLIENT_OK_CONNECTION_MESSAGE, strlen(CLIENT_OK_CONNECTION_MESSAGE));
        pthread_create(&(threadUpdate), NULL, CLIENT_updateThread, &conf.mortyRefresh);
      }

      if (commandType == LSTinderConnectionKO) {

        SINGNALS_programExit(-2, CLIENT_KO_CONNECTION_MESSAGE); //Control d'errors
      }
    }
  }
}
