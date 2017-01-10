/********************************************************************
*
* @Arxiu : seenList.h
* @Finalitat : Capçaleres de les funcions del TAD seenList.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 9 de gener del 2017
*
******************************************************************** */
#ifndef _SEENLIST_H_
	#define _SEENLIST_H_

  //Llibreries pròpies
  #include "tipus.h"

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
	SeenList SEENLIST_crea ();

	/* **********************************************
	 *
	 * @Nom : LLISTA_insereix
	 * @Definicio : Funció que permet inserir un element a la llista a l'esquerra del pdi.
	 * @Arg :  In/Out: llista = llista on s'inserirà el nou element.
	 *			   In: client = element que s'inserirà a la llista.
	 * @Ret : 0 en el cas que s'hagi produit un error, 1 en cas contrari.
	 *
	 ************************************************/
	int SEENLIST_insereix (SeenList * llista, char * name);

	char * SEENLIST_consulta(SeenList llista);

	/* **********************************************
	 *
	 * @Nom : LLISTA_busca
	 * @Definicio : Funció que permet buscar un client dintre la llista.
	 * @Arg :  In: llista = llista on s'ha de buscar.
	 *			   In: name = nom del client que s'ha de buscar a la llista.
	 * @Ret : 0 en el cas que el client no es trobi en la llista, 1 en cas contrari.
	 *
	 ************************************************/
	int SEENLIST_busca (SeenList llista, char * name);

	/* **********************************************
	 *
	 * @Nom : LLISTA_elimina
	 * @Definicio : Funció que permet eliminar un element concret de la llista.
	 * @Arg :  In/Out: llista = llista d'on s'ha d'eliminar el client.
	 *			   In: name = nom del client que s'ha d'eliminar.
	 * @Ret : 0 en el cas que el client a eliminar no es trobi en la llista, 1 en cas contrari.
	 *
	 ************************************************/
	int SEENLIST_elimina (SeenList * llista, char * name);

	/* **********************************************
	 *
	 * @Nom : LLISTA_destrueix
	 * @Definicio : Funció destructora de la llista.
	 * @Arg :  In/Out: llista = llista a destruir.
	 * @Ret : void
	 *
	 ************************************************/
	void SEENLIST_destrueix (SeenList * llista);

	void SEENLIST_vesInici(SeenList * llista);

	void SEENLIST_avanca(SeenList * llista);

	int SEENLIST_fi(SeenList llista);

#endif
