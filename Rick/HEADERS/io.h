/********************************************************************
*
* @Arxiu : io.c
* @Finalitat : Capçaleres de les funcions pel que fa l'entrada i sortida de fitxers.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 de Novembre del 2016
*
******************************************************************** */
#ifndef _IO_H_
	#define _IO_H_

	//Llibreries pròpies
	#include "signals.h"

	//Constants
	#define IO_FCONF "FILES/rick.cfg"

	//Capçaleres
	/* **********************************************
	 *
	 * @Nom : IO_readLine
	 * @Definicio : Permet llegir una cadena de caràcters en un fitxer de text fins al limitador que l'usuari desitgi.
	 * @Arg :  In: f = Punter al file descriptor d'on s'ha de llegir la línia.
	 * @Ret : Punter a una cadena de caràcter que conte la línia que s'ha llegit.
	 *
	 ************************************************/
	char * IO_readLine (int f);

	/* **********************************************
	 *
	 * @Nom : IO_readConfigurationFile
	 * @Definicio : LLegir la informació del fitxer de configuració.
	 * @Ret : Retorna la informació del fitxer de configuració tractada.
	 *
	 ************************************************/
	Configuration IO_readConfigurationFile();

#endif
