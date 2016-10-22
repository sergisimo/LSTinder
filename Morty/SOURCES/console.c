/********************************************************************
*
* @Arxiu : console.c
* @Finalitat : Implementar les funcions que permetran gestionar la consola incorporada en el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 22 d'Octubre del 2016
*
******************************************************************** */
#include "console.h"

void CONSOLE_handleCommand (char * command) {

  if (!strcmp(command, CONSOLE_SEARCH)) /*funció per buscar*/;
  else; if (!strcmp(command, CONSOLE_EXIT)) /*funció sortir del programa*/;
  else handleSystemCommand(command);
}

void CONSOLE_handleSystemCommand (char * command) {}
