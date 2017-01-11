/********************************************************************
*
* @Arxiu : conection.h
* @Finalitat : Capçalera de les funcions que permetran establir la conexio amb Ricky.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 Novembre del 2016
*
******************************************************************** */
#ifndef _CONECTION_H_
  #define _CONECTION_H_

  /**** LLIBRERIES DE SISTEMA ****/

  /**** LLIBRERIES PROPIES ****/
  #include "command.h"
  #include "io.h"
  #include "console.h"

  /**** CONSTANTS ****/
  #define CLIENT_CONECTION "[Connected]\n"
  #define CLIENT_CONECTING "\n[Conecting Rick...]\n"
  #define CONECTION_INITIALIZING_XAT "\nChat iniciat...\n"
  #define CONECTION_XAT_EXIT "exit"
  #define CONECTION_FORCE_EXIT "\nIntrodueixi EXIT siusplau!\n"
  #define CONECTION_XAT_EXIT_NOTIFICATION "\nXat tancat correctament.\n"
  #define CONECTION_XAT_ENTER_NOTIFICATION "Apreta enter per entrar al xat!\n"
  #define CONECTION_XAT_USER_LEFT "\nL'altre usuari ha sortit del xat, introdueix la comanda \"EXIT\".\n"


  /**** CAPÇALERES ****/

  /* **********************************************
   *
   * @Nom : CONECTION_preparation ()
   * @Definicio : Procediment encarregat de cridar a la funció necessaria per preparar la conexio amb el servidor Ricky.
   * @Arg : In: configuration = struct amb informació sobre la configuració que usa l'usuari.
   * @Ret : Retorna l’estructura que permet establir l’adreça ip i el port tcp.
   *
   ************************************************/
  struct sockaddr_in CONECTION_preparation();

  /* **********************************************
   *
   * @Nom : CONECTION_stablishConection ()
   * @Definicio : Procediment encarregat de cridar a la funció necessaria per establir la conexio amb el servidor Ricky.
   * @Ret : Retorna el file descriptor del socket que hem obert.
   *
   ************************************************/
   int CONECTION_stablishConection(struct sockaddr_in s_addr);

   /* **********************************************
    *
    * @Nom : CONECTION_listenServer ()
    * @Definicio : Es l'encarregat d'estar escoltant el servidor Ricky.
    * @Ret : En el nostre cas retornara null.
    *
    ************************************************/
    void* CONECTION_listenServer (void* socket);

    void CONNECTION_waitForRead();

    /* **********************************************
     *
     * @Nom : CONECTION_newConection()
     * @Definicio : Es l'encarregat del protocol de conexio amb Rick.
     *
     ************************************************/
    void CONECTION_newConection(Configuration conf, Information inf, int socket);

    /* **********************************************
     *
     * @Nom : CONECTION_desconection()
     * @Definicio : Es l'encarregat del protocol de desconexio amb Rick.
     *
     ************************************************/
    void CONECTION_desconection(Configuration conf, int socket, int valor);

    void CONECTION_connectXat(int port, char * matchName);

    void CONECTION_writeXat(int fd);

    void* CONECTION_llegirThread (void* fdAux);

#endif
