/* **********************************************
 *
 * @Arxiu : io.h
 * @Finalitat : Implementa les funcions d'entrada i sortida del programa LSTinder.
 * @Autor : Sergi Simó Bosquet - ls30685 & Esteve Genovard Ferriol - ls30742
 * @Data :  2016
 *
 ************************************************/

#ifndef _IO_H_
	#define _IO_H_

	//Llibreries del Sistema
	#include "signals.h"


	//Constantes
	#define IO_FCONF "FILES/morty.cfg"
	#define IO_FINF "FILES/morty.inf"
	#define IO_OPEN_CONFIGURATION_FILE_ERROR "\nError! El fitxer de configuracio no s'ha pogut obrir.\n"

	//Capçaleres
  /* **********************************************
   *
   * @Nom : IO_readKeyboard
   * @Definicio : Llegir informació introduida pel teclat.
   * @Ret : Punter a una cadena de caràcter que conte la cadena fins al limitador, sense incloure aquest.
   *
   ************************************************/
	char * IO_readKeyboard ();

	/* **********************************************
	 *
	 * @Nom : IO_llegirLinia
	 * @Definicio : Permet llegir una cadena de caràcters en un fitxer binari fins al limitador que l'usuari desitgi.
	 * @Arg :  In: f = Punter al file descriptor d'on s'ha de llegir la línia.
	 * @Ret : Punter a una cadena de caràcter que conte la línia que s'ha llegit.
	 *
	 ************************************************/
	char * IO_llegirLinia (int f);

	/* **********************************************
	 *
	 * @Nom : IO_llegeixFitxerConfiguration
	 * @Definicio : LLegir la informació del fitxer de configuració.
	 *
	 ************************************************/
	void IO_llegeixFitxerConfiguration();

	/* **********************************************
	 *
	 * @Nom : IO_llegeixFitxerInformation
	 * @Definicio : LLegir la informació del fitxer d'informació.
	 * @Ret : Retorna la informació del fitxer d'informació tractada.
	 *
	 ************************************************/
	Information IO_llegeixFitxerInformation();

#endif
