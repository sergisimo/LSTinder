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
		int fdClient;
		struct sockaddr_in clientSocket;
	} Client;

	/*
	*	Tipus pròpis necessaris per implementar una llista.
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
	Configuration conf;

#endif
