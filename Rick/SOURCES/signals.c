/********************************************************************
*
* @Arxiu : signals.c
* @Finalitat : Implementar les funcions necessaries per gestionar les interrupcions sobre el programa Rick.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 15 de novembre del 2016
*
******************************************************************** */
#include "../HEADERS/signals.h"

void SIGNALS_initializeSignals() {

  signal(SIGINT, SINGNALS_handleSignals);
}

void SINGNALS_handleSignals(int signal) {

  switch (signal) {
    case SIGINT:
      SINGNALS_programExit(-1, SIGNALS_SIGCONT_MESSAGE);
      break;
  }
}

void SINGNALS_programExit (int exitStatus, char * message) {

  LLISTA_destrueix(&llistaClients);

  if (!exitStatus) write(1, message, strlen(message));
  else write(2, message, strlen(message));

  exit(exitStatus);
}
