/********************************************************************
*
* @Arxiu : command.c
* @Finalitat : Funcions que conformen el TAD comanda.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 12 de Desembre del 2016
*
******************************************************************** */
#include "../HEADERS/command.h"

void COMMAND_create(Command command) {

  bzero(command, COMMAND_SIZE);
}

void COMMAND_setType(Command command, char * type) {

  int i;

  for (i = 0; i < COMMAND_TYPE_MAX && type[i] != '\0'; i++) {

    command[i] = type[i];
  }
}

void COMMAND_setInfo(Command command, char * info) {

  int i, j = 0;

  for (i = COMMAND_TYPE_MAX; i < COMMAND_INFO_MAX && info[j] != '\0'; i++) {

    command[i] = info[j];
    j++;
  }
}

void COMMAND_setData(Command command, char * data, int firstPosition) {

  int i = 0;

  while (data[i] != '\0') {

    command[firstPosition] = data[i];
    i++;
    firstPosition++;
  }
}

CommandType COMMAND_getType(Command command) {

  char type[6];

  CommandType commandType;

  int i = 0;

  while (command[i] != '\0' && i < 5) {

    type[i] = command[i];
    i++;
  }
  type[i] = '\0';

  if (!strcmp(type, COMMAND_TYPE_LSTINDER_CONNECTION_OK)) commandType = LSTinderConnectionOK;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_CONNECTION_KO)) commandType = LSTinderConnectionKO;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_CLIENT_OK)) commandType = LSTinderClientOK;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_CLIENT_KO)) commandType = LSTinderClientKO;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_DELETE_OK)) commandType = LSTinderDeleteOK;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_DELETE_KO)) commandType = LSTinderDeleteKO;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_USER)) commandType = LSTinderUser;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_USER_FI)) commandType = LSTinderFiUser;
  else if (!strcmp(type, COMMAND_TYPE_LSTINDER_MATCH)) commandType = LSTinderMatch;

  else if (!strcmp(type, COMMAND_TYPE_MORTY_CONNECTION)) commandType = MortyConnection;
  else if (!strcmp(type, COMMAND_TYPE_MORTY_DISCONNECTION)) commandType = MortyDisconnection;
  else if (!strcmp(type, COMMAND_TYPE_MORTY_NEXT)) commandType = MortyNext;
  else if (!strcmp(type, COMMAND_TYPE_MORTY_LIKE)) commandType = MortyLike;

  return commandType;
}

CommandInfo COMMAND_getInfo(Command command) {

  char info[10];

  CommandInfo commandInfo;

  int i = 5, j = 0;

  while (command[i] != '\0' && j < 10) {

    info[j] = command[i];
    i++;
    j++;
  }
  info[j] = '\0';

  if (!strcmp(info, COMMAND_INFO_MORTY_CONNECTION)) commandInfo = MortyConnectionInfo;
  else if (!strcmp(info, COMMAND_INFO_MORTY_NEXT)) commandInfo = MortyNextInfo;
  else if (!strcmp(info, COMMAND_INFO_MORTY_LIKE)) commandInfo = MortyLikeInfo;
  else if (!strcmp(info, COMMAND_INFO_LSTINDER_USER)) commandInfo = LSTinderUserInfo;

  return commandInfo;
}

int COMMAND_getPort(Command command) {

  char info[10];

  int i = 5, j = 0;

  while (command[i] != '\0' && j < 10) {

    info[j] = command[i];
    i++;
    j++;
  }
  info[j] = '\0';

  return atoi(info);
}

char * COMMAND_getData(Command command, int start, int final) {

  char * destination;

  int i, j = 0;

  destination = (char *) malloc(sizeof(char)*(final-start+2));

  if (destination == NULL) SINGNALS_programExit(-1, SIGNALS_MEMORY_ERROR); //Control d'errors
  else {

    for (i = start; i <= final && command[i] != '\0'; i++) {

      destination[j] = command[i];
      j++;
    }

    destination[j] = '\0';
  }

  if (strlen(destination) != 0) {
    destination = realloc(destination, sizeof(char)*strlen(destination));
    if (destination == NULL) SINGNALS_programExit(-1, SIGNALS_MEMORY_ERROR);
  }

  return destination;
}
