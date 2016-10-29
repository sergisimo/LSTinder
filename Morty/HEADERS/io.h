/* **********************************************
 *
 * @Arxiu : tipus.h
 * @Finalitat : Implementa tots els tipus propis del programa LSTinder
 * @Autor : Sergi Simó Bosquet - ls30685 & Esteve Genovard Ferriol - ls30742
 * @Data :  2016
 *
 ************************************************/

#ifndef _IO_H_
	#define _IO_H_

	//Llibreries del Sistema
	#include "tipus.h"
	#include <fcntl.h>
	#include <unistd.h>

	//Constantes
	#define FCONF "files/morty.cfg"
	#define FINF "files/morty.inf"

	//Capçaleres
  /* **********************************************
   *
   * @Nom : FITXERS_llegirCadena
   * @Definicio : Permet llegir una cadena de caràcters en un fitxer binari fins al limitador que l'usuari desitgi.
   * @Arg : In: f = Punter al fitxer des del que s'ha de llegir la cadena.
   *            limitador = Caràcter fins al qual es desitga llegir la cadena.
   * @Ret : Punter a una cadena de caràcter que conte la cadena fins al limitador, sense incloure aquest.
   *
   ************************************************/
	char * IO_readKeyboard ();

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : FITXERS_llegirCadena
	 * @Definicio : Permet llegir una cadena de caràcters en un fitxer binari fins al limitador que l'usuari desitgi.
	 * @Arg : In: f = Punter al fitxer des del que s'ha de llegir la cadena.
	 *            limitador = Caràcter fins al qual es desitga llegir la cadena.
	 * @Ret : Punter a una cadena de caràcter que conte la cadena fins al limitador, sense incloure aquest.
	 *
	 ************************************************/
	char * IO_llegirLinia (int f);

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : FITXERS_llegirCadena
	 * @Definicio : Permet llegir una cadena de caràcters en un fitxer binari fins al limitador que l'usuari desitgi.
	 * @Arg : In: f = Punter al fitxer des del que s'ha de llegir la cadena.
	 *            limitador = Caràcter fins al qual es desitga llegir la cadena.
	 * @Ret : Punter a una cadena de caràcter que conte la cadena fins al limitador, sense incloure aquest.
	 *
	 ************************************************/
	Configuration IO_llegeixFitxerConfiguration();

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : FITXERS_llegirCadena
	 * @Definicio : Permet llegir una cadena de caràcters en un fitxer binari fins al limitador que l'usuari desitgi.
	 * @Arg : In: f = Punter al fitxer des del que s'ha de llegir la cadena.
	 *            limitador = Caràcter fins al qual es desitga llegir la cadena.
	 * @Ret : Punter a una cadena de caràcter que conte la cadena fins al limitador, sense incloure aquest.
	 *
	 ************************************************/
	Information IO_llegeixFitxerInformation();

#endif
