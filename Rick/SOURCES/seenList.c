/********************************************************************
*
* @Arxiu : seenList.c
* @Finalitat : Implementar les funcions necessaries per gestionar la llista on es guardaran els noms de els Morty vistos.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 10 de gener del 2017
*
******************************************************************** */
#include "../HEADERS/seenList.h"

SeenList SEENLIST_crea () {

  SeenList llista;

	llista.pri = (NodeSeen*) malloc (sizeof(NodeSeen));

	if (llista.pri != NULL) {

			llista.ant = llista.pri;
			llista.pri->seg = NULL;
	}

	return llista;
}

int SEENLIST_insereix(SeenList * llista, char * name) {

  NodeSeen * aux;

  aux = (NodeSeen *) malloc (sizeof(NodeSeen));
  if (aux == NULL) {
    return 0;
  }
  else {

    aux->name = name;
    aux->seg = llista->ant->seg;
    llista->ant->seg = aux;
    return 1;
  }
}

char * SEENLIST_consulta(SeenList llista) {

  return llista.ant->seg->name;
}

int SEENLIST_busca(SeenList llista, char * name) {

  llista.ant = llista.pri;

  while (llista.ant->seg != NULL) {

    if (!strcmp(llista.ant->seg->name, name)) return 1;
    llista.ant = llista.ant->seg;
  }

  return 0;
}

int SEENLIST_elimina(SeenList * llista, char * name) {

  NodeSeen * aux;

  llista->ant = llista->pri;

  while (llista->ant->seg != NULL) {

    if (!strcmp(llista->ant->seg->name, name)) {

      aux = llista->ant->seg;
      llista->ant->seg = llista->ant->seg->seg;
      free(aux->name);
      free(aux);
      return 1;
    }

    llista->ant = llista->ant->seg;
  }

  return 0;
}

void SEENLIST_destrueix(SeenList * llista) {

  NodeSeen * aux;

  llista->ant = llista->pri;

  while (llista->ant->seg != NULL) {

    aux = llista->ant;
    llista->ant = llista->ant->seg;

    if (aux != llista->pri) free(aux->name);

    free(aux);
  }

  if (llista->ant != llista->pri) free(llista->ant->name);

  free(llista->ant);
}

int SEENLIST_isCreated(SeenList llista) {

  return llista.pri != NULL && llista.ant != NULL;
}

void SEENLIST_vesInici(SeenList * llista) {

  llista->ant = llista->pri;
}

void SEENLIST_avanca(SeenList * llista) {

  llista->ant = llista->ant->seg;
}

int SEENLIST_fi(SeenList llista) {

  return llista.ant->seg == NULL;
}
