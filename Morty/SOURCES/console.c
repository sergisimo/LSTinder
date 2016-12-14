/********************************************************************
*
* @Arxiu : console.c
* @Finalitat : Implementar les funcions que permetran gestionar la consola incorporada en el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 22 d'Octubre del 2016
*
******************************************************************** */
#include "../HEADERS/console.h"

void enviaLike(Configuration configuration, char * nom, Command commanda, int socket){
  //ENVIAMENT
  COMMAND_create(commanda);
  COMMAND_setType(commanda, COMMAND_TYPE_RICK_LIKE);
  COMMAND_setInfo(commanda, COMMAND_INFO_RICK_LIKE);
  COMMAND_setData(commanda, configuration.userName, 15);
  COMMAND_setData(commanda, nom, 30);

  write(socket, commanda, COMMAND_SIZE);
}
void enviaNovaPeticio(Command commanda, int socket){
  //ENVIAMENT
  COMMAND_create(commanda);
  COMMAND_setType(commanda, COMMAND_TYPE_RICK_NEXT);
  COMMAND_setInfo(commanda, COMMAND_INFO_RICK_NEXT);

  write(socket, commanda, COMMAND_SIZE);
}

int CONSOLE_handleCommand (char * command, Configuration configuration, int socket) {

  Command commanda;
  char * contesta;
  CommandType commandType;
  CommandInfo commandInfo;
  char * * usuaris;
  int END = 0, correcte = 1, i = 0, first = 1;

  if (!CONSOLE_compareStrings(command, CONSOLE_SEARCH)) {
    char promptN[50];
    write(1, CONSOLE_SEARCH_RESPONSE, strlen(CONSOLE_SEARCH_RESPONSE));

    enviaNovaPeticio(commanda, socket);

    do{
      //RESPOSTA
      read(socket, commanda, COMMAND_SIZE);
      commandType = COMMAND_getType(commanda);
      commandInfo = COMMAND_getInfo(commanda);

      if (commandType == RickNewMorty && commandInfo == RickNewMortyInfo && first) {
         usuaris = (char**)malloc(sizeof(usuaris) * 1);
         first = 0;
         if(usuaris){
           usuaris[0] = (char*)malloc(sizeof (char) * 15);
           usuaris[0] = COMMAND_getData(commanda, 25, 39);
           write(1, COMMAND_getData(commanda, 15, 24), strlen(COMMAND_getData(commanda, 15, 24)));
           write(1,"\n",1);
           write(1, COMMAND_getData(commanda, 25, 39), strlen(COMMAND_getData(commanda, 25, 39)));
           write(1,"\n",1);
           write(1, COMMAND_getData(commanda, 40, 41), strlen(COMMAND_getData(commanda, 40, 41)));
           write(1,"\n",1);
           write(1, COMMAND_getData(commanda, 42, 114), strlen(COMMAND_getData(commanda, 42, 114)));
           write(1, "\nLike? (Si/No/END)\n", strlen("\nLike? (YES/NO/END)\n"));
           do {
               sprintf(promptN, "\n%s >> ", configuration.userName);
               write(1, promptN, strlen(promptN));
               contesta = IO_readKeyboard();
               correcte = 1;
               if (strcmp(contesta, "END")){
                 END = 1;
               } else {
                 if (strcmp(contesta, "YES")){
                    enviaLike(configuration, COMMAND_getData(commanda, 25, 39), commanda, socket);
                    enviaNovaPeticio(commanda, socket);
                 } else {
                   if (strcmp(contesta, "NO")){
                      enviaNovaPeticio(commanda, socket);
                   } else {
                      correcte = 0;
                      write(1, "\nIntrodueix: Si/No/END\n", strlen("\nIntrodueix: Si/No/END\n"));
                   }
                 }
               }
             }while(correcte);
          } else {
              write(1, "Error demanant memoria!", strlen("Error demanant memoria!"));
          }
      } else {
           if (commandType == RickNewMorty && commandInfo == RickNewMortyInfo && !first) {
              usuaris = (char**)realloc(usuaris, sizeof(usuaris)*1);
              if(usuaris){
                i++;
                usuaris[i] = (char *)malloc(sizeof (char)* 15);
                usuaris[i] = COMMAND_getData(commanda, 25, 39);
                write(1, COMMAND_getData(commanda, 15, 24), strlen(COMMAND_getData(commanda, 15, 24)));
                write(1,"\n",1);
                write(1, COMMAND_getData(commanda, 25, 39), strlen(COMMAND_getData(commanda, 25, 39)));
                write(1,"\n",1);
                write(1, COMMAND_getData(commanda, 40, 41), strlen(COMMAND_getData(commanda, 40, 41)));
                write(1,"\n",1);
                write(1, COMMAND_getData(commanda, 42, 114), strlen(COMMAND_getData(commanda, 42, 114)));
                write(1, "\nLike? (Si/No/END)\n", strlen("\nLike? (YES/NO/END)\n"));
                do {
                    sprintf(promptN, "\n%s >> ", configuration.userName);
                    write(1, promptN, strlen(promptN));
                    contesta = IO_readKeyboard();
                    correcte = 1;
                    if (strcmp(contesta, "END")){
                      END = 1;
                    } else {
                      if (strcmp(contesta, "YES")){
                         enviaLike(configuration, COMMAND_getData(commanda, 25, 39), commanda, socket);
                         enviaNovaPeticio(commanda, socket);
                      } else {
                        if (strcmp(contesta, "NO")){
                           enviaNovaPeticio(commanda, socket);
                        } else {
                           correcte = 0;
                           write(1, "\nIntrodueix: Si/No/END\n", strlen("\nIntrodueix: Si/No/END\n"));
                        }
                      }
                    }
                  }while(correcte);
               } else {
                   write(1, "Error demanant memoria!", strlen("Error demanant memoria!"));
               }
            } else {
                write(1, "\nError en la comunicació amb el servidor!\n", strlen("\nError en la comunicació amb el servidor!\n"));
            }
      }

    }while(!END);

    return 0;
  }

  if (!CONSOLE_compareStrings(command, CONSOLE_EXIT)) {
    CONECTION_desconection(configuration, socket, 1);
    return 1;
  } else {
    CONSOLE_handleSystemCommand(command);
    return 0;
  }
}

void CONSOLE_handleSystemCommand (char * command) {

  char ** commandSplited;
  int size, fill, status, statusLinux;

  commandSplited = CONSOLE_split(command, ' ', &size);

  fill = fork();
  switch (fill) {
    case -1:
      SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR);
      break;
    case 0:
      write(1, "\n", 1);
      statusLinux = execvp(commandSplited[0], commandSplited);
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

  commandSplited = (char **) realloc(commandSplited, sizeof(char *)*(j+1));
  if (commandSplited == NULL) {
    SINGNALS_programExit(-1, CONSOLE_MEMORY_ALLOCATION_ERROR);
  }

  commandSplited[j+1] = NULL;

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
