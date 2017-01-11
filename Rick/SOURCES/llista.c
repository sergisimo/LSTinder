/********************************************************************
*
* @Arxiu : llista.c
* @Finalitat : Implementar les funcions necessaries per gestionar una llista.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 15 de novembre del 2016
*
******************************************************************** */
#include "../HEADERS/llista.h"

Llista LLISTA_crea () {

  Llista llista;

	llista.pri = (Node*) malloc (sizeof(Node));

	if (llista.pri != NULL) {

			llista.ant = llista.pri;
			llista.pri->seg = NULL;
	}

	return llista;
}

int LLISTA_insereix(Llista * llista, Client client) {

  Node * aux;

  aux = (Node *) malloc (sizeof(Node));
  if (aux == NULL) {
    return 0;
  }
  else {

    aux->e = client;
    aux->seg = llista->ant->seg;
    llista->ant->seg = aux;
    return 1;
  }
}

Client LLISTA_consulta(Llista llista) {

  return llista.ant->seg->e;
}

int LLISTA_busca(Llista llista, char * name) {

  llista.ant = llista.pri;

  while (llista.ant->seg != NULL) {

    if (!strcmp(llista.ant->seg->e.nickName, name)) return 1;
    llista.ant = llista.ant->seg;
  }

  return 0;
}

int LLISTA_elimina(Llista * llista, char * name) {

  Node * aux;

  llista->ant = llista->pri;

  while (llista->ant->seg != NULL) {

    if (!strcmp(llista->ant->seg->e.nickName, name)) {

      aux = llista->ant->seg;
      llista->ant->seg = llista->ant->seg->seg;
      free(aux->e.nickName);
      free(aux->e.info.name);
      free(aux->e.info.description);
      free(aux);
      return 1;
    }

    llista->ant = llista->ant->seg;
  }

  return 0;
}

void LLISTA_destrueix(Llista * llista) {

  Node * aux;

  llista->ant = llista->pri;

  while (llista->ant->seg != NULL) {

    aux = llista->ant;
    llista->ant = llista->ant->seg;

    if (aux != llista->pri) {
      free(aux->e.nickName);
      free(aux->e.info.name);
      free(aux->e.info.description);
      close(aux->e.fdClient);
    }
    free(aux);
  }

  if (llista->ant != llista->pri) {
    free(llista->ant->e.nickName);
    free(llista->ant->e.info.name);
    free(llista->ant->e.info.description);
    if (SEENLIST_isCreated(llista->ant->e.seenList)) SEENLIST_destrueix(&llista->ant->e.seenList);
    close(llista->ant->e.fdClient);
  }

  free(llista->ant);
}

void LLISTA_vesInici(Llista * llista) {

  llista->ant = llista->pri;
}

void LLISTA_avanca(Llista * llista) {

  llista->ant = llista->ant->seg;
}

int LLISTA_fi(Llista llista) {

  return llista.ant->seg == NULL;
}
