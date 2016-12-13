/********************************************************************
*
* @Arxiu : signals.c
* @Finalitat : Implementar les funcions necessaries per gestionar les interrupcions sobre el programa Rick.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 15 de novembre del 2016
*
******************************************************************** */
#include "../HEADERS/signals.h"

pthread_mutex_t semaforLlista = PTHREAD_MUTEX_INITIALIZER;

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

  if (exitStatus != -2) {
    pthread_mutex_lock(&semaforLlista);
    LLISTA_destrueix(&llistaClients);
    pthread_mutex_unlock(&semaforLlista);
    pthread_mutex_destroy(&semaforLlista);
  }

  close(conf.serverSockedFD);
  close(conf.clientSocketFD);

  if (!exitStatus) write(1, message, strlen(message));
  else write(2, message, strlen(message));

  exit(exitStatus);
}
