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
  //s_addr.sin_addr.s_addr = INADDR_ANY;
  inet_aton (configuration.addr, &s_addr.sin_addr);
  return s_addr;
}

int  CONECTION_stablishConection(struct sockaddr_in s_addr){

  int sfd;

  sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  write (2, "[Conecting Rick...]\n", strlen("[Conecting Rick...]\n"));
  if (sfd < 0)  SINGNALS_programExit(-1, SOCKET_ERROR); //Control d'errors
  else {
    if (connect(sfd, (void *) &s_addr, sizeof(s_addr)) < 0)  SINGNALS_programExit(-1, CONECTION_ERROR); //Control d'errors
    else {

    }
  }
  return sfd;

}

void* CONECTION_listenServer (void* socket) {

  int info;
  //char aux[10];
  int sdf = *((int*)socket);

  //do{
    read(sdf, &info, sizeof(int));
    //sprintf(aux, "%d\n", info);
    //write(1, aux, strlen(aux));
  //}while(1);

  return NULL;
}

void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void midaParaules(char n[],int num, char nom[]){
  int i = strlen(n);
  if (strlen(n) >= (unsigned)num){
    for (i = 0; i < num; i++){
      nom[i]=n[i];
    }
    nom[i -1]='\0';
  }else{
    for (i = 0; i < num; i++){
      if(strlen(n) < (unsigned)i){
        nom[i]='\0';
      }else{
        nom[i]=n[i];
      }
    }
    nom[i -1]='\0';
  }
}

void afegeixParaula (char n[], char nom[], int num){
  int i = 0;
  int a = 0;
  switch (num) {
    case 1:
      i = 15;
      for (i = 15; i < 25; i++){
        n[i] = nom[a];
        a++;
      }
    break;
    case 2:
      i = 25;
      for (i = 25; i < 40; i++){
        n[i] = nom[a];
        a++;
      }
    break;
    case 3:
      i = 40;
      for (i = 40; i < 42; i++){
        n[i] = nom[a];
        a++;
      }
    break;
    case 4:
      i = 42;
      for (i = 42; i < 115; i++){
        n[i] = nom[a];
        a++;
      }
    break;
    case 5:
      i = 15;
      for (i = 15; i < 115; i++){
        n[i] = nom[a];
        a++;
      }
    break;
  }
}

void CONECTION_newConection(Configuration conf, Information inf, int socket){
  char tramaCon[115]="CONCLINFO\0\0\0\0\0\0";
  char nom[10], nick[15], age[2], descripcio[73];
  char * tipo;
  char * ppal;

  //ENVIAMENT
  midaParaules(inf.name, 10, nom);
  afegeixParaula(tramaCon, nom, 1);
  midaParaules(conf.userName, 15, nick);
  afegeixParaula(tramaCon, nick, 2);
  itoa(12, age);
  if (strlen(age) < 2){
    age[1]= '\0';
  }
  afegeixParaula(tramaCon, age, 3);
  midaParaules(inf.description, 73, descripcio);
  afegeixParaula(tramaCon, descripcio, 4);
  write(socket, tramaCon, 115);
  //RESPOSTA
  read(socket, tramaCon, 115);
  tipo = CONECTION_substring(tramaCon, 0, 4);
  ppal = CONECTION_substring(tramaCon, 5, 14);
   if (!strcmp(tipo, CLIENT_TYPE_CONNECT)){
     if(!strcmp(ppal, CLIENT_TYPE_CONNECT_OK)){
       write(1, "[Connected]\n", strlen("[Connected]\n"));
       pthread_t threads;
       pthread_create(&threads, NULL, CONECTION_listenServer, &socket);
     }
     else{
       SINGNALS_programExit(-1, CLIENT_CONECTION_ERROR); //Control d'errors
     }
   }else{
     SINGNALS_programExit(-1, CLIENT_CONECTION_ERROR); //Control d'errors
   }

}

void CONECTION_desconection(Configuration conf, int socket){
  char tramaCon[115]="DESC\0\0\0\0\0\0\0\0\0\0\0", nick[100];
  char * tipo;
  char * ppal;

  //ENVIAMENT
  midaParaules(conf.userName, 100, nick);
  afegeixParaula(tramaCon, nick, 5);
  write(socket, tramaCon, 115);

  //RESPOSTA
  read(socket, tramaCon, 115);
  tipo = CONECTION_substring(tramaCon, 0, 4);
  ppal = CONECTION_substring(tramaCon, 5, 14);
  if (!strcmp(tipo, CLIENT_TYPE_DISCONNECT)){
     if(!strcmp(ppal, CLIENT_TYPE_DISCONNECT_OK)){
       	close(socket);
       SINGNALS_programExit(0, CONSOLE_EXIT_RESPONSE);
     }
     else{
       SINGNALS_programExit(-1, CLIENT_DISCONECTION_ERROR); //Control d'errors
     }
  }else{
     SINGNALS_programExit(-1, CLIENT_DISCONECTION_ERROR); //Control d'errors
  }
}

char * CONECTION_substring(char * string, int start, int final) {

  char * destination;

  int i, j = 0;

  destination = (char *) malloc(sizeof(char)*(final-start+2));

  if (destination == NULL) SINGNALS_programExit(-1, CLIENT_MEMORY_ERROR); //Control d'errors
  else {
    for (i = start; i <= final; i++) {

      destination[j] = string[i];
      j++;
    }

    destination[j] = '\0';
  }

  return destination;
}
