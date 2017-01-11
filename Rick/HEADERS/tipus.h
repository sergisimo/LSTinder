/* **********************************************
 *
 * @Arxiu : tipus.h
 * @Finalitat : Implementa tots els tipus propis del programa Rick.
 * @Autor : Sergi Simó Bosquet - ls30685 & Esteve Genovard Ferriol - ls30742
 * @Data Creació:  8 de Novembre del 2016
 *
 ************************************************/
#ifndef _TIPUS_H_
	#define _TIPUS_H_

	//Llibreries del Sistema
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <conio.h>
	#include <fcntl.h>
	#include <unistd.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <sys/socket.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <pthread.h>

	//Tipus Propis
	/*
	*	Tipus per la llista dels vistos.
	*/
	typedef struct _node_ {

		char * name;
		struct _node_ * seg;
	} NodeSeen;

	typedef struct {

		NodeSeen * pri;
		NodeSeen * ant;
	} SeenList;

	/*
	* Tipus propi que permet guardar les caràcteristiques del fitxer rick.cfg.
	*/
  typedef struct {

    int mortyRefresh;
		int serverSockedFD;
		int clientSocketFD;
    struct sockaddr_in serverConf;
    struct sockaddr_in clientConf;
  } Configuration;

	/*
	* Tipus propi que permet guardar les dades dels clients Morty que es connecten.
	*/
	typedef struct {

		char * name;
		int age;
		char * description;
	} Information;

	typedef struct {

		char * nickName;
		Information info;
		SeenList seenList;
		int fdClient;
		pthread_t threadClient;
		struct sockaddr_in clientSocket;
	} Client;

	/*
	*	Tipus pròpis necessaris per implementar les comandes que s'utilitzaran per la comunicació client servidor.
	*/
	typedef char Command[115];

	/*
	*	Enumeració per tal de oder gestionar els tipus de comandes.
	*/
	typedef enum {

		LSTinderConnectionOK,
		LSTinderConnectionKO,
		LSTinderClientOK,
		LSTinderClientKO,
		LSTinderDeleteOK,
		LSTinderDeleteKO,
		LSTinderUser,
		LSTinderFiUser,
		LSTinderMatch,
		MortyConnection,
		MortyDisconnection,
		MortyNext,
		MortyLike
	}CommandType;

	/*
	*	Enumeració per tal de oder gestionar la info de comandes.
	*/
	typedef enum {

		LSTinderUserInfo,
		MortyConnectionInfo,
		MortyNextInfo,
		MortyLikeInfo
	}CommandInfo;

	/*
	*	Tipus per la llista dels clients.
	*/
	typedef struct _node {

		Client e;
		struct _node * seg;
	} Node;

	typedef struct {

		Node * pri;
		Node * ant;
	} Llista;

	//Variables globals
	Llista llistaClients;
	Llista llistaMortys;
	Configuration conf;
	int update;
	pthread_t threadUpdate;
	Command commandReaded;
	int waitRead;

#endif
