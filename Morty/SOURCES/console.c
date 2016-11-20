/********************************************************************
*
* @Arxiu : console.c
* @Finalitat : Implementar les funcions que permetran gestionar la consola incorporada en el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 22 d'Octubre del 2016
*
******************************************************************** */
#include "../HEADERS/console.h"

int CONSOLE_handleCommand (char * command, Configuration configuration, int socket) {

  if (!CONSOLE_compareStrings(command, CONSOLE_SEARCH)) {
    write(1, CONSOLE_SEARCH_RESPONSE, strlen(CONSOLE_SEARCH_RESPONSE));
    return 0;
  }

  if (!CONSOLE_compareStrings(command, CONSOLE_EXIT)) {
    CONECTION_desconection(configuration, socket);
    return 1;
  } else {
    CONSOLE_handleSystemCommand(command);
    return 0;
  }
}

void CONSOLE_handleSystemCommand (char * command) {

  char ** commandSplited;
  int size, fill, status, i, statusLinux;

  commandSplited = CONSOLE_split(command, ' ', &size);
  strcpy(command, commandSplited[0]);
  for(i = 1; i < size; i++) {
    strcpy(commandSplited[i-1], commandSplited[i]);
  }
  commandSplited = (char **)realloc(commandSplited, sizeof(char*)*(size-1));

  if (commandSplited == NULL) {
    commandSplited = (char **) malloc (sizeof(char*));
    commandSplited[0] = (char*)  malloc (sizeof(char));
    commandSplited[0][0] = '\0';
  }

  fill = fork();
  switch (fill) {
    case -1:
      SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR);
      break;
    case 0:
      write(1, "\n", 1);
      statusLinux = execvp(command, commandSplited);
      if (statusLinux == -1) write(2, CONSOLE_NOT_FOUND_COMMAND, strlen(CONSOLE_NOT_FOUND_COMMAND));
      exit(0);
      break;
    default:
      wait(&status);
      break;
  }

  free(command);
  free(commandSplited);
}

char ** CONSOLE_split(char * command, char splitChar, int * size) {

  int i = 0, j = 0, k = 0;

  char ** commandSplited = (char **) malloc (sizeof(char*));
  if (commandSplited == NULL) SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR); //Control d'errors.
  else {
    commandSplited[j] = (char *)malloc(sizeof(char));
    if (commandSplited[k] == NULL) SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR); //Control d'errors.
    else {
      while (command[i] != '\0') {
        if (command[i] != splitChar) {
          commandSplited[j][k] = command[i];
          k++;
          i++;
          commandSplited[j] = (char *) realloc(commandSplited[j], sizeof(char)*(k+1));
          if (commandSplited[j] == NULL) {
            SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR);
            break;
          }
        } else {
          commandSplited[j][k] = '\0';
          k = 0;
          i++;
          j++;
          commandSplited = (char **) realloc(commandSplited, sizeof(char *)*(j+1));
          commandSplited[j] = (char *)malloc(sizeof(char));
          if (commandSplited == NULL) {
            SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR);
            break;
          }
        }
      }
      commandSplited[j][k] = '\0';
    }
  }

  *size = j+1;
  return commandSplited;

}

int CONSOLE_compareStrings (char * str1, char * str2) {

  int i = 0;
  char c;

  if (strlen(str1) != strlen(str2)) return 1;
  else {
    while (str1[i] != '\0') {
      if (str1[i] >= 'a' && str1[i] <= 'z') {
        c = 'A' + (str1[i] - 'a');
      } else {
        if (str1[i] >= 'A' && str1[i] <= 'Z') {
          c = 'a' + (str1[i] - 'A');
        } else {
          c = str1[i];
        }
      }
      if (str1[i] != str2[i] && c != str2[i]) return 1;
      i++;
    }
  }
  return 0;
}

void CONSOLE_start (Configuration configuration, int socket) {

  int sortir = 0;

  char * command;
  char prompt[50];

  while (!sortir) {

    sprintf(prompt, "\n%s >> ", configuration.userName);
    write(1, prompt, strlen(prompt));
    command = IO_readKeyboard();
    sortir = CONSOLE_handleCommand(command, configuration, socket);
  }

}
