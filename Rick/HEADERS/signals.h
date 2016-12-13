/********************************************************************
*
* @Arxiu : signals.h
* @Finalitat : Capçaleres de les funcions que gestionen les interrupcions en el programa Rick.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 15 de novembre del 2016
*
******************************************************************** */
#ifndef _SIGNALS_H_
	#define _SIGNALS_H_

  //Llibreries pròpies
	#include "llista.h"

  //Constants
	#define SIGNALS_SIGCONT_MESSAGE "\nInterrupció rebuda! Abortant el programa de forma segura.\n"
	#define SIGNALS_MEMORY_ERROR "Error al demanar memòria!\n"
	#define SIGNALS_SOCKET_ERROR "Error al crear el socket!\n"
	#define SIGNALS_BIND_ERROR "Error al crear el bind!\n"

	extern pthread_mutex_t semaforLlista;

  //Capçaleres
	/* **********************************************
   *
   * @Nom : SIGNALS_initializeSignals
   * @Definicio : Inicialitza totes les interrupcions que s'han de controlar en el programa i les redirigeix a la funció handle.
   * @Arg :  void
   * @Ret : void
   *
   ************************************************/
	void SIGNALS_initializeSignals();

	/* **********************************************
	 *
	 * @Nom : SINGNALS_handleSignals
	 * @Definicio : Permet gestionar totes les interrupcions necessaries per el programa i crida a les funcions que requereixi cada una.
	 * @Arg :  In = identificador del signal que ha fet saltar la funció.
	 * @Ret : void
	 *
	 ************************************************/
	void SINGNALS_handleSignals(int signal);

	/* **********************************************
	 *
	 * @Nom : SINGNALS_programExit
	 * @Definicio : Permet sortir del programa de forma segura, eliminant tota la memòria dinàmica.
	 * @Arg :  In = nombre de sortida que tindrà el programa quan tanqui la seva execució.
	 *				 In = misstge que es mostrarà al ususari abans de acabar el programa.
	 * @Ret : void
	 *
	 ************************************************/
	void SINGNALS_programExit (int exitStatus, char * message);

#endif
