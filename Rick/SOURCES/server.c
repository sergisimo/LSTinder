/********************************************************************
*
* @Arxiu : server.c
* @Finalitat : Implementar les funcions necessaries per poder crear un servidor.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 de Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/server.h"

void SERVER_connect(Configuration *configuration) {

  configuration->serverSockedFD = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (configuration->serverSockedFD < 0) {

    SINGNALS_programExit(-2, SIGNALS_SOCKET_ERROR);
  } else {

    if (bind(configuration->serverSockedFD, (void *) &(configuration->serverConf), sizeof(configuration->serverConf)) < 0) {

      SINGNALS_programExit(-2, SIGNALS_BIND_ERROR);
    } else {

      listen(configuration->serverSockedFD, SERVER_MAX_CONNECTIONS);
      write(1, SERVER_ON_MESSAGE, strlen(SERVER_ON_MESSAGE));
    }
  }
}

void* SERVER_clientThread(void * clientPointer) {

  Client client = *((Client *)clientPointer);
  free(clientPointer);

  int sortir = 0, status;

  char aux[50];

  Command command;

  COMMAND_create(command);

  while (!sortir) {

    status = read(client.fdClient, command, COMMAND_SIZE);

    if (status != 0) sortir = SERVER_handleRequest(command, client);
    else {

      sprintf(aux, "Exiting %s\n", client.nickName);

      pthread_mutex_lock(&semaforLlista);
      LLISTA_elimina(&llistaClients, client.nickName);
      pthread_mutex_unlock(&semaforLlista);

      write(1, aux, strlen(aux));
      close(client.fdClient);
      sortir = 1;
    }
  }

  return NULL;
}

void SERVER_listenClients(Configuration configuration) {

  Command command;
  char aux[50];

  int connectionStatus;

  Client * client;
  socklen_t c_len;
  pthread_t threadAux;

  llistaClients = LLISTA_crea();
  COMMAND_create(command);

  while (1) {

    client = (Client *) malloc(sizeof(Client));
    if (client == NULL) SINGNALS_programExit(-1, SIGNALS_MEMORY_ERROR);

    c_len = sizeof(client->clientSocket);
    client->fdClient = accept(configuration.serverSockedFD, (void *) &(client->clientSocket), &c_len);

    read(client->fdClient, command, COMMAND_SIZE);
    connectionStatus = SERVER_handleConnex(command, client);

    sprintf (aux, "Peticio new morty %s\n", client->nickName);
    write(1, aux, strlen(aux));

    if (connectionStatus) {

      write(1, SERVER_CONNECTION_OK, strlen(SERVER_CONNECTION_OK));

      pthread_mutex_lock(&semaforLlista);
      LLISTA_insereix(&llistaClients, *client);
      pthread_mutex_unlock(&semaforLlista);

      SERVER_sendResponse(*client, SERVER_OK_CONNECTION_ID);
      pthread_create(&(threadAux), NULL, SERVER_clientThread, client);
    } else {
      SERVER_sendResponse(*client, SERVER_KO_CONNECTION_ID);
      write(1, SERVER_CONNECTION_KO, strlen(SERVER_CONNECTION_KO));
    }
  }
}

void SERVER_sendResponse(Client client, int type) {

  Command command;

  COMMAND_create(command);

  switch (type) {
    case SERVER_OK_CONNECTION_ID:

      COMMAND_setType(command, COMMAND_TYPE_MORTY_CONNECTION);
      COMMAND_setInfo(command, COMMAND_INFO_MORTY_CONNECTION_OK);
      break;

    case SERVER_KO_CONNECTION_ID:

      COMMAND_setType(command, COMMAND_TYPE_MORTY_CONNECTION);
      COMMAND_setInfo(command, COMMAND_INFO_MORTY_CONNECTION_KO);
      break;

    case SERVER_OK_DISCONNECTION_ID:

      COMMAND_setType(command, COMMAND_TYPE_MORTY_DISCONNECTION);
      COMMAND_setInfo(command, COMMAND_INFO_MORTY_DISCONNECTION_OK);
      break;

    case SERVER_KO_DISCONNECTION_ID:

      COMMAND_setType(command, COMMAND_TYPE_MORTY_DISCONNECTION);
      COMMAND_setInfo(command, COMMAND_INFO_MORTY_DISCONNECTION_KO);
      break;
  }

  write(client.fdClient, command, COMMAND_SIZE);
}

int SERVER_handleConnex(Command command, Client * client) {

  CommandType commandType = COMMAND_getType(command);
  CommandInfo commandInfo = COMMAND_getInfo(command);

  // FER LA PART DE LA INFO **********************
  if (commandType == MortyConnection && commandInfo == MortyConnectionInfo) {

    client->info.name = COMMAND_getData(command, 15, 24);
    client->nickName = COMMAND_getData(command, 25, 39);
    client->info.age = atoi(COMMAND_getData(command, 40, 41));
    client->info.description = COMMAND_getData(command, 42, 114);

    pthread_mutex_lock(&semaforLlista);
    if (LLISTA_busca(llistaClients, client->nickName)) {
      pthread_mutex_unlock(&semaforLlista);
      return 0;
    } else {
      pthread_mutex_unlock(&semaforLlista);
      return 1;
    }
  } else return 0;
}

int SERVER_handleRequest(Command command, Client client) {

  char aux[50];

  switch (COMMAND_getType(command)) {

    case MortyDisconnection:

      sprintf(aux, "Exiting %s\n", client.nickName);
      pthread_mutex_lock(&semaforLlista);
      if (LLISTA_elimina(&llistaClients, client.nickName)) {
        pthread_mutex_unlock(&semaforLlista);
        SERVER_sendResponse(client, SERVER_OK_DISCONNECTION_ID);
        write(1, aux, strlen(aux));
        close(client.fdClient);
        return 1;
      } else {
        pthread_mutex_unlock(&semaforLlista);
        SERVER_sendResponse(client, SERVER_KO_DISCONNECTION_ID);
        return 0;
      }
      break;

      default:
        break;
  }

  return 0;
}
