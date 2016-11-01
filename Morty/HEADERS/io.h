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
	#include "tipus.h"


	//Constantes
	#define FCONF "FILES/morty.cfg"
	#define FINF "FILES/morty.inf"

	//Capçaleres
  /* **********************************************
   *
   * @Nom : IO_readKeyboard
   * @Definicio : Llegir informació introduida pel teclat.
   * @Ret : Punter a una cadena de caràcter que conte la cadena fins al limitador, sense incloure aquest.
   *
   ************************************************/
	char * IO_readKeyboard ();

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : IO_llegirLinia
	 * @Definicio : Permet llegir una cadena de caràcters en un fitxer binari fins al limitador que l'usuari desitgi.
	 * @Arg :  In: f = Punter al file descriptor d'on s'ha de llegir la línia.
	 * @Ret : Punter a una cadena de caràcter que conte la línia que s'ha llegit.
	 *
	 ************************************************/
	char * IO_llegirLinia (int f);

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : IO_llegeixFitxerConfiguration
	 * @Definicio : LLegir la informació del fitxer de configuració.
	 * @Ret : Retorna la informació del fitxer de configuració tractada.
	 *
	 ************************************************/
	Configuration IO_llegeixFitxerConfiguration();

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : IO_llegeixFitxerInformation
	 * @Definicio : LLegir la informació del fitxer d'informació.
	 * @Ret : Retorna la informació del fitxer d'informació tractada.
	 *
	 ************************************************/
	Information IO_llegeixFitxerInformation();

#endif
