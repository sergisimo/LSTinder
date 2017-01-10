/********************************************************************
*
* @Arxiu : signals.h
* @Finalitat : Capçalera de les funcions que permetran gestionar les interrupcions llençades contra el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 1 de Novembre del 2016
*
******************************************************************** */
#ifndef _SIGNALS_H_
  #define _SIGNALS_H_

  /**** LLIBRERIES DE SISTEMA ****/

  /**** LLIBRERIES PROPIES ****/
  #include "tipus.h"
  #include "conection.h"

  /**** CONSTANTS ****/
  #define SIGNALS_SIGCONT_MESSAGE    "\nPrograma interromput! Abortant de forma segura...\n\n"
  #define SIGNALS_MEMORY_ERROR "Error al demanar memòria!\n"
  #define SIGNALS_SOCKET_ERROR "Socket_KO"
  #define SIGNALS_CONECTION_ERROR "[can't connect Rick]\n\n"
  #define SIGNALS_CLIENT_CONECTION_ERROR "[ERROR Usuari ja connectat]\n"
  #define SIGNALS_CLIENT_DISCONECTION_ERROR "\nError al desconnectar ja que el servidor es troba fora de servei. Disculpi per les molesties.\n\n"
  #define SIGNALS_EXIT_MESSAGE "\nEsperem que hagis trobat el teu Morty ideal.\n\n"
  #define SIGNALS_COMMUNICATION_ERROR "\nError en la comunicació amb el servidor!\n"

  /**** CAPÇALERES ****/
  /* **********************************************
   *
   * @Nom : SIGNALS_initializeSignals
   * @Definicio : Procediment encarregat d'inicialitzar totes les interrupcions indicant quina función han d'executar en ser llençades.
   * @Arg : void
   * @Ret : void
   *
   ************************************************/
  void SIGNALS_initializeSignals();

  /* **********************************************
   *
   * @Nom : SINGNALS_handleSignals
   * @Definicio : Procediment encarregat d'indicar que s'ha de realitzar depenent en la interrupció que s'ha llençat.
   * @Arg : In: signal = signal que ha rebut el programa.
   * @Ret : void
   *
   ************************************************/
  void SINGNALS_handleSignals(int signal);

  /* **********************************************
   *
   * @Nom : SINGNALS_programExit
   * @Definicio : Procediment encarregat d'alliberar tota la memòria i sortir del programa.
   * @Arg : In: exitStatus = enter amb el qual es realitzarà el exit del programa.
   *            message = cadena de caràcters que conté el missatge que se li ha de mostrar al usuari.
   * @Ret : void
   *
   ************************************************/
  void SINGNALS_programExit(int exitStatus, char * message);


#endif
