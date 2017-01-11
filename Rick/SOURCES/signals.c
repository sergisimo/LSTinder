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
pthread_mutex_t semaforLlistaMortys = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semaforComanda = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semaforWait = PTHREAD_MUTEX_INITIALIZER;

void SIGNALS_initializeSignals() {

  signal(SIGINT, SIGNALS_handleSignals);
  signal(SIGALRM, SIGNALS_handleSignals);
  signal(SIGUSR1, SIGNALS_handleSignals);
}

void SIGNALS_handleSignals(int signal) {

  switch (signal) {
    case SIGINT:

      SINGNALS_programExit(-1, SIGNALS_SIGCONT_MESSAGE);
      break;

    case SIGALRM:

      update = 1;
      pthread_kill(threadUpdate, SIGUSR1);
      break;

    default:
      break;
  }
}

void SINGNALS_programExit (int exitStatus, char * message) {

  if (exitStatus != -2) {
    pthread_mutex_lock(&semaforLlista);
    LLISTA_destrueix(&llistaClients);
    pthread_mutex_unlock(&semaforLlista);
    pthread_mutex_destroy(&semaforLlista);
    pthread_mutex_lock(&semaforLlistaMortys);
    LLISTA_destrueix(&llistaMortys);
    pthread_mutex_unlock(&semaforLlistaMortys);
    pthread_mutex_destroy(&semaforLlistaMortys);
    pthread_mutex_destroy(&semaforComanda);
    pthread_mutex_destroy(&semaforWait);
  }

  close(conf.serverSockedFD);
  close(conf.clientSocketFD);

  if (!exitStatus) write(1, message, strlen(message));
  else write(2, message, strlen(message));

  exit(exitStatus);
}
