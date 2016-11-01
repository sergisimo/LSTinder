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
	#include <sys/wait.h>

	//Tipus Propis
	/*
	* Tipus propi que permet guardar les caràcteristiques del fitxer morty.cfg.
	*/
	typedef struct {
		char * userName;
		char * addr;
    int sin_port;
	} Configuration;

	/*
	* Tipus propi que permet guardar les caràcteristiques del fitxer morty.inf.
	*/
	typedef struct {
		char * name;
		int age;
		char * description;
	} Information;

	Configuration configuration;
	Information information;

#endif
