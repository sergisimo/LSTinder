/********************************************************************
*
* @Arxiu : main.c
* @Finalitat : Implementar el procediment principal del programa Rick.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 de Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/server.h"

int main () {

  //Configuration conf = IO_readConfigurationFile();

  Llista l = LLISTA_crea();
  Client c1, c2, c3;

  c1.name = (char *)malloc(sizeof(char)*20);
  c2.name = (char *)malloc(sizeof(char)*20);
  c3.name = (char *)malloc(sizeof(char)*20);

  strcpy(c1.name, "Jordi");
  strcpy(c2.name, "Sergi");
  strcpy(c3.name, "Esteve");

  LLISTA_insereix(&l, c1);
  LLISTA_insereix(&l, c2);
  LLISTA_insereix(&l, c3);

  printf("ESTEVE: %d\n", LLISTA_busca(l, "Esteve"));
  printf("MANEL: %d\n", LLISTA_busca(l, "Manel"));

  LLISTA_elimina(&l, "Esteve");
  printf("JORDI: %d\n", LLISTA_busca(l, "Jordi"));
  printf("ESTEVE: %d\n", LLISTA_busca(l, "Esteve"));
  printf("SERGI: %d\n", LLISTA_busca(l, "Sergi"));

  LLISTA_destrueix(&l);

  return 0;
}
