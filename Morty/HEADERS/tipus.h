/* **********************************************
 *
 * @Arxiu : tipus.h
 * @Finalitat : Implementa tots els tipus propis del programa LSTinder
 * @Autor : Sergi Simó Bosquet - ls30685 & Esteve Genovard Ferriol - ls30742
 * @Data :  2016
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
	#include <sys/types.h>
	#include <pthread.h>
	#include <sys/wait.h>
	#include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
	#include <arpa/inet.h>
  #include <unistd.h>
  #include <fcntl.h>

	//Tipus Propis
	/*
	* Tipus propi que permet guardar les caràcteristiques del fitxer morty.cfg.
	*/
	typedef struct {
		char * userName;
		char * addr;
    int sin_port;
		int sock;
	} Configuration;

	/*
	* Tipus propi que permet guardar les caràcteristiques del fitxer morty.inf.
	*/
	typedef struct {
		char * name;
		int age;
		char * description;
	} Information;

	/*
	*	Tipus pròpis necessaris per implementar les comandes que s'utilitzaran per la comunicació client servidor.
	*/
	typedef char Command[115];

	/*
	* Enumeration per saber quin tipus de trama hem rebut del servidor.
	*/
	typedef enum {

		RickMatch,
		RickConnection,
		RickDisconnection,
		RickNewMorty,
		RickLike,
		MortyXat
	} CommandType;

	/*
	* Enumeration per saber quina info de trama hem rebut del servidor.
	*/
	typedef enum {

		RickConnectionOK,
		RickConnectionKO,
		RickDisconnectionOK,
		RickDisconnectionKO,
		RickNewMortyInfo,
		RickNoMorty,
		RickLikeInfo,
		MortyXatExit
	} CommandInfo;

	Configuration configuration;
	Information information;

#endif
