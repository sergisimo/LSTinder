/********************************************************************
*
* @Arxiu : server.h
* @Finalitat : Capçaleres de les funcions necessaries per poder crear un servidor.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 de Novembre del 2016
*
******************************************************************** */
#ifndef _SERVER_H_
	#define _SERVER_H_

  //Llibreries pròpies
  #include "llista.h"
	#include "io.h"
	#include "command.h"

  //Constants
  #define SERVER_MAX_CONNECTIONS 20

	#define SERVER_CONNECTION_OK "Peticio OK\n"
	#define SERVER_CONNECTION_KO "Peticio KO, usuari ja existent.\n"
	#define SERVER_ON_MESSAGE "Rick >> Sense connexions\n\n"

	#define SERVER_OK_CONNECTION_ID 1
	#define SERVER_KO_CONNECTION_ID 2
	#define SERVER_OK_DISCONNECTION_ID 3
	#define SERVER_KO_DISCONNECTION_ID 4

  //Capçaleres
  /* **********************************************
   *
   * @Nom : SERVER_connect
   * @Definicio : Connecta el servidor amb la informació passada com a paràmetre i el deix llest per rebre clients.
   * @Arg :  In/Out: configuration = Punter al struct que conté la configuració del server i en el qual afegim el file descriptor del servidor.
   * @Ret : void
   *
   ************************************************/
  void SERVER_connect(Configuration *configuration);

	void* SERVER_clientThread(void * clientPointer);

	void SERVER_listenClients(Configuration configuration);

	void SERVER_sendResponse(Client client, int type);

	int SERVER_handleConnex(Command command, Client * client);

	int SERVER_handleRequest(Command command, Client client);

#endif
