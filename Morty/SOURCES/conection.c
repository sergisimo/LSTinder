/********************************************************************
*
* @Arxiu : conection.c
* @Finalitat : Implementar les funcions que premetran establir la conexio amb Ricky
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/conection.h"

struct sockaddr_in CONECTION_preparation(){

  struct sockaddr_in s_addr;

  memset (&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(configuration.sin_port);
  inet_aton (configuration.addr, &s_addr.sin_addr);

  return s_addr;
}

int  CONECTION_stablishConection(struct sockaddr_in s_addr){

  int sfd;

  sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  write (1, CLIENT_CONECTING, strlen(CLIENT_CONECTING));
  if (sfd < 0)  SINGNALS_programExit(-1, SIGNALS_SOCKET_ERROR); //Control d'errors
  else {
    if (connect(sfd, (void *) &s_addr, sizeof(s_addr)) < 0)  SINGNALS_programExit(-1, SIGNALS_CONECTION_ERROR); //Control d'errors
  }

  return sfd;
}

//    ACTIVAR THREAD QUAN SIGUI NECESSARI
void* CONECTION_listenServer (void* socket) {

  int sdf = *(int*)socket;

  CommandType commandType;
  char * matchName;
  int matchPort;

  free(socket);

  COMMAND_create(commandReaded);

  do {
    read(sdf, commandReaded, COMMAND_SIZE);


    commandType = COMMAND_getType(commandReaded);

    if (commandType != RickMatch) {
      waitRead = 1;
      kill(getpid(), SIGUSR1);
    } else{

      matchPort = COMMAND_getPort(commandReaded);
      matchName = COMMAND_getData(commandReaded, 15, 29);

      CONECTION_connectXat(matchPort, matchName);
    }
  } while(1);

  return NULL;
}

void CONNECTION_waitForRead() {

  waitRead = 0;

  while(!waitRead) pause();
}

void CONECTION_newConection(Configuration conf, Information inf, int socket){

  Command command;
  CommandType commandType;
  CommandInfo commandInfo;
  int * socketAux;

  char age[3];
  sprintf(age, "%d", inf.age);

  //ENVIAMENT
  COMMAND_create(command);
  COMMAND_setType(command, COMMAND_TYPE_RICK_CONNECTION);
  COMMAND_setInfo(command, COMMAND_INFO_RICK_CONNECTION);
  COMMAND_setData(command, inf.name, 15);
  COMMAND_setData(command, conf.userName, 25);
  COMMAND_setData(command, age, 40);
  COMMAND_setData(command, inf.description, 42);

  write(socket, command, COMMAND_SIZE);

  //RESPOSTA
  read(socket, command, COMMAND_SIZE);
  commandType = COMMAND_getType(command);
  commandInfo = COMMAND_getInfo(command);

   if (commandType == RickConnection && commandInfo == RickConnectionOK){

     write(1, CLIENT_CONECTION, strlen(CLIENT_CONECTION));
     socketAux = (int *) malloc (sizeof(int));
     *socketAux = socket;

     pthread_t threads;
     pthread_create(&threads, NULL, CONECTION_listenServer, socketAux);   //ACTIVAR THREAD QUAN SIGUI NECESSARI
   }else{

     SINGNALS_programExit(-1, SIGNALS_CLIENT_CONECTION_ERROR); //Control d'errors
   }
}

void CONECTION_desconection(Configuration conf, int socket, int valor){

  Command command;
  CommandType commandType;
  CommandInfo commandInfo;

  //ENVIAMENT
  COMMAND_create(command);
  COMMAND_setType(command, COMMAND_TYPE_RICK_DISCONNECTION);
  COMMAND_setData(command, conf.userName, 15);

  write(socket, command, COMMAND_SIZE);

  //RESPOSTA
  CONNECTION_waitForRead();

  commandType = COMMAND_getType(commandReaded);
  commandInfo = COMMAND_getInfo(commandReaded);

  if (commandType == RickDisconnection && commandInfo == RickDisconnectionOK) {

    close(socket);

    if (valor) SINGNALS_programExit(0, SIGNALS_EXIT_MESSAGE);
    else SINGNALS_programExit(0, SIGNALS_SIGCONT_MESSAGE);
  } else {

     SINGNALS_programExit(-1, SIGNALS_CLIENT_DISCONECTION_ERROR); //Control d'errors
  }
}

void CONECTION_connectXat(int port, char * matchName) {

  int sfd;
  struct sockaddr_in s_addr;
  char aux[50];

  sprintf(aux, "\n%s>> NEW MATCH AMB %s REBUT\n", configuration.userName, matchName);
  write(1, aux, strlen(aux));
  stopped = 1;

  memset (&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(port);
  inet_aton(configuration.addr, &s_addr.sin_addr);

  sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sfd < 0)  SINGNALS_programExit(-1, SIGNALS_SOCKET_ERROR); //Control d'errors
  else {
    if (connect(sfd, (void *) &s_addr, sizeof(s_addr)) < 0)  SINGNALS_programExit(-1, SIGNALS_CONECTION_ERROR);
    else {
      configuration.xatFD = sfd;
      CONECTION_writeXat(sfd);
    }
  }
}

void CONECTION_writeXat(int fd) {

  int sortir = 0, correcte = 0;
  char * text;
  int * exit;
  char aux[100];
  Command command;
  Xat * xatAux = (Xat *) malloc (sizeof(Xat));
  pthread_t llegirThread;

  xatAux->fd = fd;
  COMMAND_create(command);
  pthread_create(&llegirThread, NULL, CONECTION_llegirThread, xatAux);
  xatAux->idMemComp = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0600);

  exit = shmat(xatAux->idMemComp, 0, 0);
  *exit = 0;

  if (!reading) write(1, CONECTION_INITIALIZING_XAT, strlen(CONECTION_INITIALIZING_XAT));

  while (!sortir) {

    sprintf(aux, "%s >> ", configuration.userName);
    write(1, aux, strlen(aux));
    if (reading) write(1, CONECTION_XAT_ENTER_NOTIFICATION, strlen(CONECTION_XAT_ENTER_NOTIFICATION));
    text = IO_readKeyboard();
    if (strlen(text) > 80); //errors
    else {

      if (*exit == 1) {
        do {
          if (!CONSOLE_compareStrings(text, CONECTION_XAT_EXIT)) {
            COMMAND_setType(command, COMMAND_TYPE_MORTY_XAT);
            COMMAND_setInfo(command, COMMAND_INFO_MORTY_XAT_EXIT);

            write(fd, command, COMMAND_SIZE);
            correcte = 1;
            sortir = 1;
          } else {
            write(1, CONECTION_FORCE_EXIT, strlen(CONECTION_FORCE_EXIT));
            sprintf(aux, "%s >> ", configuration.userName);
            write(1, aux, strlen(aux));
            text = IO_readKeyboard();
          }
        } while(!correcte);

      } else {

        if (!CONSOLE_compareStrings(text, CONECTION_XAT_EXIT)) {

          COMMAND_setType(command, COMMAND_TYPE_MORTY_XAT);
          COMMAND_setInfo(command, COMMAND_INFO_MORTY_XAT_EXIT);

          write(fd, command, COMMAND_SIZE);

          sortir = 1;
          *exit = 1;

        } else {
          sprintf(aux, "%s >> %s", configuration.userName, text);

          COMMAND_create(command);
          COMMAND_setType(command, COMMAND_TYPE_MORTY_XAT);
          COMMAND_setData(command, aux, 15);

          write(fd, command, COMMAND_SIZE);
        }
      }
    }
  }

  stopped = 0;
  kill(getpid(), SIGUSR1);
  shmctl(xatAux->idMemComp, IPC_RMID, NULL);
  close(fd);
  write(1, CONECTION_XAT_EXIT_NOTIFICATION, strlen(CONECTION_XAT_EXIT_NOTIFICATION));
}

void* CONECTION_llegirThread (void* fdAux) {

  Xat xatAux = *((Xat *)fdAux);
  int sortir = 0;
  int * exit;
  Command command;
  CommandInfo commandInfo;
  char * aux;
  char aux2[20];

  free(fdAux);
  COMMAND_create(command);
  exit = shmat(xatAux.idMemComp, 0, 0);

  while (!sortir) {

    read(xatAux.fd, command, COMMAND_SIZE);

    commandInfo = COMMAND_getInfo(command);

    if (commandInfo == MortyXatExit) {

      if (!(*exit)) {
        write(1, CONECTION_XAT_USER_LEFT, strlen(CONECTION_XAT_USER_LEFT));
        sprintf(aux2, "%s >> ", configuration.userName);
        write(1, aux2, strlen(aux));
      }
      *exit = 1;
      sortir = 1;
    } else {

      aux = COMMAND_getData(command, 15, 114);

      write(1, "\n", 1);
      write(1, aux, strlen(aux));

      sprintf(aux, "\n%s >> ", configuration.userName);
      write(1, aux, strlen(aux));
    }
  }

  return NULL;
}
