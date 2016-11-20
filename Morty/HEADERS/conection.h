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
  #include "signals.h"


  /**** CONSTANTS ****/
  #define CLIENT_MEMORY_ERROR "Peticion_KO"
  #define CLIENT_CONECTION_ERROR "[ERROR Usuari ja connectat]\n"
  #define CLIENT_DISCONECTION_ERROR "Disconection_ERROR"
  #define SOCKET_ERROR "Socket_KO"
  #define CONECTION_ERROR "[can't connect Rick]\n"
  #define CLIENT_TYPE_CONNECT "CONCL"
  #define CLIENT_TYPE_CONNECT_OK "OK_CONEX"
  #define CLIENT_TYPE_CONNECT_KO "KO_CONEX"
  #define CLIENT_TYPE_DISCONNECT "DESC-"
  #define CLIENT_TYPE_DISCONNECT_OK "OK_DESC"
  #define CLIENT_TYPE_DISCONNECT_KO "KO_DESC"
  #define CONSOLE_EXIT_RESPONSE "\nEsperem que hagis trobat el teu Morty ideal.\n\n"

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

    void* CONECTION_listenServer (void* socket) ;

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

    void CONECTION_desconection(Configuration conf, int socket);

    /* **********************************************
     *
     * @Nom : CONECTION_substring ()
     * @Definicio : Es l'encarregat de desparsetgar la informació.
     * @Ret : Retorna la cadena parsetgada.
     *
     ************************************************/

    char * CONECTION_substring(char * string, int start, int final);


#endif
