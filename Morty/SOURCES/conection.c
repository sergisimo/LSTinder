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

/*    ACTIVAR THREAD QUAN SIGUI NECESSARI
void* CONECTION_listenServer (void* socket) {

  int info;
  int sdf = *((int*)socket);

  do{
    read(sdf, &info, sizeof(int));
    //Tractar resposta
  }while(1);

  return NULL;
}*/

void CONECTION_newConection(Configuration conf, Information inf, int socket){

  Command command;
  CommandType commandType;
  CommandInfo commandInfo;

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
     //pthread_t threads;
     //pthread_create(&threads, NULL, CONECTION_listenServer, &socket);   ACTIVAR THREAD QUAN SIGUI NECESSARI
   }else{

     SINGNALS_programExit(-1, SIGNALS_CLIENT_CONECTION_ERROR); //Control d'errors
   }
}

void CONECTION_desconection(Configuration conf, int socket, int valor){

  Command command;
  CommandType commandType;
  CommandInfo commandInfo;

  //ENVIAMENT
  COMMAND_setType(command, COMMAND_TYPE_RICK_DISCONNECTION);
  COMMAND_setData(command, conf.userName, 15);

  write(socket, command, COMMAND_SIZE);

  //RESPOSTA
  read(socket, command, COMMAND_SIZE);

  commandType = COMMAND_getType(command);
  commandInfo = COMMAND_getInfo(command);

  if (commandType == RickDisconnection && commandInfo == RickDisconnectionOK) {

    close(socket);

    if (valor) SINGNALS_programExit(0, SIGNALS_EXIT_MESSAGE);
    else SINGNALS_programExit(0, SIGNALS_SIGCONT_MESSAGE);
  } else {

     SINGNALS_programExit(-1, SIGNALS_CLIENT_DISCONECTION_ERROR); //Control d'errors
  }
}
