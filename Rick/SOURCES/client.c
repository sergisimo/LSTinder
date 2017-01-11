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

    CLIENT_waitForRead(command);

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
  pthread_t listenThread;
  int * socketAux;

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

        socketAux = (int *) malloc (sizeof(int));
        *socketAux = configuration->clientSocketFD;

        pthread_create(&listenThread, NULL, CLIENT_listenLSTinder, socketAux);
      }

      if (commandType == LSTinderConnectionKO) {

        SINGNALS_programExit(-2, CLIENT_KO_CONNECTION_MESSAGE); //Control d'errors
      }
    }
  }
}

void* CLIENT_listenLSTinder (void* socket) {

  int sdf = *(int*)socket;
  free(socket);

  Command commandAux;
  Client clientAux;
  CommandType commandType;
  int matchStatus = -1;
  int sortir = 0;

  do {

    read(sdf, commandAux, COMMAND_SIZE);

    pthread_mutex_lock(&semaforComanda);
    COMMAND_copy(commandReaded, commandAux);
    commandType = COMMAND_getType(commandReaded);


    if (commandType != LSTinderMatch) {

      pthread_mutex_lock(&semaforWait);
      waitRead = 1;
      pthread_mutex_unlock(&semaforWait);

      if (commandType == LSTinderFiUser || commandType == LSTinderUser) pthread_kill(threadUpdate, SIGUSR1);
      if (commandType == LSTinderClientOK || commandType == LSTinderClientKO) kill(getpid(), SIGUSR1);
      if (commandType == LSTinderDeleteOK || commandType == LSTinderDeleteKO) {
        pthread_mutex_lock(&semaforLlista);
        LLISTA_vesInici(&llistaClients);
        sortir = 0;
        while (!LLISTA_fi(llistaClients) && !sortir) {

          clientAux = LLISTA_consulta(llistaClients);

          if (clientAux.fdClient == COMMAND_getPort(commandReaded)) {
            pthread_kill(clientAux.threadClient, SIGUSR1);
            sortir = 1;
          }

          LLISTA_avanca(&llistaClients);
        }
        pthread_mutex_unlock(&semaforLlista);
      }
    } else {

      int port = COMMAND_getPort(commandReaded);
      char * name1 = COMMAND_getData(commandReaded, 15, 29);
      char * name2 = COMMAND_getData(commandReaded, 30, 44);
      pthread_mutex_unlock(&semaforComanda);
      SERVER_sendMatch(port, name1, name2, &matchStatus);
    }
  } while(1);

  return NULL;
}

void CLIENT_waitForRead(Command command) {

  pthread_mutex_lock(&semaforWait);
  waitRead = 0;

  while(!waitRead) {
    pthread_mutex_unlock(&semaforWait);
    pause();
    pthread_mutex_lock(&semaforWait);
  }

  pthread_mutex_unlock(&semaforWait);

  COMMAND_copy(command, commandReaded);
  pthread_mutex_unlock(&semaforComanda);
}
