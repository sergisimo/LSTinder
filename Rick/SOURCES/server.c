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

    SINGNALS_programExit(-1, SERVER_SOCKET_ERROR);
  } else {

    if (bind(configuration->serverSockedFD, (void *) &(configuration->serverConf), sizeof(configuration->serverConf)) < 0) {

      SINGNALS_programExit(-1, SERVER_BIND_ERROR);
    } else {

      listen(configuration->serverSockedFD, SERVER_MAX_CONNECTIONS);
      write(1, SERVER_ON_MESSAGE, strlen(SERVER_ON_MESSAGE));
    }
  }
}

void* SERVER_clientThread(void * clientPointer) {

  Client client = *((Client *)clientPointer);
  int sortir = 0;

  char buffer[115];

  while (!sortir) {

    read(client.fdClient, buffer, 115);
    sortir = SERVER_handleRequest(buffer, client);
  }

  return NULL;
}

void SERVER_listenClients(Configuration configuration) {

  char buffer[115];
  char aux[50];

  int connectionStatus;

  Client client;
  socklen_t c_len;
  pthread_t threadAux;

  llistaClients = LLISTA_crea();

  while (1) {

    c_len = sizeof(client.clientSocket);
    client.fdClient = accept(configuration.serverSockedFD, (void *) &client.clientSocket, &c_len);

    read(client.fdClient, buffer, 115);
    connectionStatus = SERVER_handleConnex(buffer, &client);

    sprintf (aux, "Peticio new morty %s\n", client.nickName);
    write(1, aux, strlen(aux));

    if (connectionStatus) {

      write(1, SERVER_CONNECTION_OK, strlen(SERVER_CONNECTION_OK));
      LLISTA_insereix(&llistaClients, client);
      client = LLISTA_consulta(llistaClients);
      SERVER_sendResponse(client, SERVER_OK_CONNECTION_ID);
      pthread_create(&(threadAux), NULL, SERVER_clientThread, &client);
    } else {
      SERVER_sendResponse(client, SERVER_KO_CONNECTION_ID);
      write(1, SERVER_CONNECTION_KO, strlen(SERVER_CONNECTION_KO));
    }
  }
}

void SERVER_sendResponse(Client client, int type) {

  char buffer[115];

  int i;

  switch (type) {
    case SERVER_OK_CONNECTION_ID:
      strcpy(buffer, SERVER_RESPONSE_CONNECTION_OK);
      for (i = 14; i < 115; i++) buffer[i] = '\0';
      write(client.fdClient, buffer, 115);
      break;
    case SERVER_KO_CONNECTION_ID:
      strcpy(buffer, SERVER_RESPONSE_CONNECTION_KO);
      for (i = 14; i < 115; i++) buffer[i] = '\0';
      write(client.fdClient, buffer, 115);
      break;
    case SERVER_OK_DISCONNECTION_ID:
      strcpy(buffer, SERVER_RESPONSE_DISCONNECTION_OK);
      for (i = 12; i < 115; i++) buffer[i] = '\0';
      write(client.fdClient, buffer, 115);
      break;
    case SERVER_KO_DISCONNECTION_ID:
      strcpy(buffer, SERVER_RESPONSE_DISCONNECTION_KO);
      for (i = 12; i < 115; i++) buffer[i] = '\0';
      write(client.fdClient, buffer, 115);
      break;
  }
}

int SERVER_handleConnex(char * buffer, Client * client) {

  char * type;
  char * info;

  type = SERVER_substring(buffer, 0, 4);
  info = SERVER_substring(buffer, 5, 14);

  if (!strcmp(type, SERVER_TYPE_CONNECT) && !strcmp(info, SERVER_INFO_CONNECT)) {

    client->info.name = SERVER_substring(buffer, 15, 24);
    client->nickName = SERVER_substring(buffer, 25, 39);
    client->info.age = atoi(SERVER_substring(buffer, 40, 41));
    client->info.description = SERVER_substring(buffer, 42, 114);

    free(type);
    free(info);

    if (LLISTA_busca(llistaClients, client->nickName)) return 0;
    else return 1;
  } else {

    free(type);
    free(info);
    return 0;
  }
}

int SERVER_handleRequest(char * buffer, Client client) {

  char * type;
  char aux[50];
  char * nickName;

  type = SERVER_substring(buffer, 0, 4);

  if (!strcmp(type, SERVER_TYPE_DISCONNECT)) {

    nickName = SERVER_substring(buffer, 15, 29);

    if (LLISTA_elimina(&llistaClients, nickName)) {

      SERVER_sendResponse(client, SERVER_OK_DISCONNECTION_ID);
      sprintf(aux, "Exiting %s\n", client.nickName);
      write(1, aux, strlen(aux));
      //close(client.fdClient);
      return 1;
    }
    else {
      SERVER_sendResponse(client, SERVER_KO_DISCONNECTION_ID);
      return 0;
    }
  }

  return 0;
}

char * SERVER_substring(char * string, int start, int final) {

  char * destination;

  int i, j = 0;

  destination = (char *) malloc(sizeof(char)*(final-start+2));

  if (destination == NULL) SINGNALS_programExit(-1, SERVER_MEMORY_ERROR); //Control d'errors
  else {
    for (i = start; i <= final && string[i] != '\0'; i++) {

      destination[j] = string[i];
      j++;
    }

    destination[j] = '\0';
  }

  destination = realloc(destination, sizeof(char)*strlen(destination));

  return destination;
}
