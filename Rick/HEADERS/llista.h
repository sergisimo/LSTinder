/********************************************************************
*
* @Arxiu : llista.h
* @Finalitat : Capçaleres de les funcions del TAD llista.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 15 de novembre del 2016
*
******************************************************************** */
#ifndef _LLISTA_H_
	#define _LLISTA_H_

  //Llibreries pròpies
	#include "seenList.h"

  //Constants

  //Capçaleres
	/* **********************************************
	 *
	 * @Nom : LLISTA_crea
	 * @Definicio : Funció constructura de la llista.
	 * @Arg :  void
	 * @Ret : Llista correctament creada.
	 *
	 ************************************************/
	Llista LLISTA_crea ();

	/* **********************************************
	 *
	 * @Nom : LLISTA_insereix
	 * @Definicio : Funció que permet inserir un element a la llista a l'esquerra del pdi.
	 * @Arg :  In/Out: llista = llista on s'inserirà el nou element.
	 *			   In: client = element que s'inserirà a la llista.
	 * @Ret : 0 en el cas que s'hagi produit un error, 1 en cas contrari.
	 *
	 ************************************************/
	int LLISTA_insereix (Llista * llista, Client client);

	Client LLISTA_consulta(Llista llista);

	/* **********************************************
	 *
	 * @Nom : LLISTA_busca
	 * @Definicio : Funció que permet buscar un client dintre la llista.
	 * @Arg :  In: llista = llista on s'ha de buscar.
	 *			   In: name = nom del client que s'ha de buscar a la llista.
	 * @Ret : 0 en el cas que el client no es trobi en la llista, 1 en cas contrari.
	 *
	 ************************************************/
	int LLISTA_busca (Llista llista, char * name);

	/* **********************************************
	 *
	 * @Nom : LLISTA_elimina
	 * @Definicio : Funció que permet eliminar un element concret de la llista.
	 * @Arg :  In/Out: llista = llista d'on s'ha d'eliminar el client.
	 *			   In: name = nom del client que s'ha d'eliminar.
	 * @Ret : 0 en el cas que el client a eliminar no es trobi en la llista, 1 en cas contrari.
	 *
	 ************************************************/
	int LLISTA_elimina (Llista * llista, char * name);

	/* **********************************************
	 *
	 * @Nom : LLISTA_destrueix
	 * @Definicio : Funció destructora de la llista.
	 * @Arg :  In/Out: llista = llista a destruir.
	 * @Ret : void
	 *
	 ************************************************/
	void LLISTA_destrueix (Llista * llista);

	void LLISTA_vesInici(Llista * llista);

	void LLISTA_avanca(Llista * llista);

	int LLISTA_fi(Llista llista);

#endif
