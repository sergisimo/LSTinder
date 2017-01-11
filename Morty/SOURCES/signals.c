/********************************************************************
*
* @Arxiu : console.c
* @Finalitat : Implementar les funcions que permetran gestionar les interrupcions llençades contra el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 1 de Novembre del 2016
*
******************************************************************** */
#include "../HEADERS/signals.h"

void SIGNALS_initializeSignals() {

  signal(SIGINT, SINGNALS_handleSignals);
  signal(SIGUSR1, SINGNALS_handleSignals);
}

void SINGNALS_handleSignals(int signal) {

  switch (signal) {
    case SIGINT:
      CONECTION_desconection(configuration, configuration.sock, 0);
      break;
  }
}

void SINGNALS_programExit (int exitStatus, char * message) {

  free(configuration.userName);
  free(configuration.addr);
  free(information.name);
  free(information.description);

  if (!exitStatus) write(1, message, strlen(message));
  else write(2, message, strlen(message));

  exit(exitStatus);
}
