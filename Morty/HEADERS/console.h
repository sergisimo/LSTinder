/********************************************************************
*
* @Arxiu : console.h
* @Finalitat : Capçalera de les funcions que permetran gestionar la consola incorporada en el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 22 d'Octubre del 2016
*
******************************************************************** */
#ifndef _CONSOLE_H_
  #define _CONSOLE_H_

  /**** LLIBRERIES DE SISTEMA ****/

  /**** LLIBRERIES PROPIES ****/
  #include "io.h"
  #include "conection.h"

  /**** CONSTANTS ****/
  #define CONSOLE_SEARCH  "search"
  #define CONSOLE_EXIT    "exit"
  #define CONSOLE_YES    "yes"
  #define CONSOLE_NO    "no"
  #define CONSOLE_END    "end"
  #define CONSOLE_SEARCH_RESPONSE    "\nComanda identificada!\n"
  #define CONSOLE_EXIT_RESPONSE    "\nEsperem que hagis trobat el teu Morty ideal.\n\n"
  #define CONSOLE_NOT_FOUND_COMMAND    "Comanda inexistent!\n"
  #define CONSOLE_MEMORY_ALLOCATION_ERROR    "\nNo s'ha pogut reservar suficient espaic de memòria. Abortant de forma segura...\n\n"
  #define CONSOLE_LIKE_PROMPT "\nLike? (YES/NO/END)\n"
  #define CONSOLE_LIKE_PROMPT_ALERT "\nIntrodueix: YES/NO/END\n"
  #define CONSOLE_NO_NEXT "\nNo hi ha més Mortys\n"

  /**** CAPÇALERES ****/

  /* **********************************************
   *
   * @Nom : CONSOLE_handleCommand
   * @Definicio : Procediment encarregat de cridar a la funció necessaria segons la comanda que entri l'usuari.
   * @Arg : In: command = cadena de caràcters amb la comanda que ha entrat l'usuari, amb tots els arguments.
   * @Ret : Retorna 0 -> Si s'ha de sortir del programa.
   *        Retorna 1 -> Si no s'ha de tancar el programa.
   *
   ************************************************/
  int CONSOLE_handleCommand(char * command, Configuration configuration, int socket);

  /* **********************************************
   *
   * @Nom : CONSOLE_handleSystemCommand
   * @Definicio : Procediment encarregat de tractar i realitzar una crida al sistema linux.
   * @Arg : In: command = cadena de caràcters amb la comanda de Linux a realitzar, amb tots els arguments.
   * @Ret : void
   *
   ************************************************/
  void CONSOLE_handleSystemCommand (char * command);

  void CONSOLE_search(int socket);

  void CONSOLE_enviaLike(Configuration configuration, char * nom, Command commanda, int socket);

  void CONSOLE_enviaNovaPeticio(Command commanda, int socket);

  /* **********************************************
   *
   * @Nom : CONSOLE_split
   * @Definicio : Procediment encarregat de separar la comanda pel delimitador que vulgui l'usuari.
   * @Arg : In: command = cadena de caràcters amb la comanda de Linux a realitzar, amb tots els arguments.
   *        In: splitChar = caràcter amb el delimitador pel qual es vol separar la cadena.
   *        Out: size = enter que conté la mida de l'array de cadenes que es retorna.
   * @Ret : Array de cadenes de caràcter amb la comanda separada pels espais.
   *
   ************************************************/
  char ** CONSOLE_split(char * command, char splitChar, int * size);

  /* **********************************************
   *
   * @Nom : CONSOLE_compareStrings
   * @Definicio : Procediment encarregat de comparar de forma case insensitive dos cadenes de caràcter.
   * @Arg : In: str1 = cadena de caràcters amb la primera que s'ha de comparar
   *        In: str2 = cadena de caràcters amb la segona que s'ha de comparar
   * @Ret : Retorna 0 -> Si les cadenes són iguals.
   *        Retorna 1 -> Si les cadenes són diferents.
   *
   ************************************************/
  int CONSOLE_compareStrings (char * str1, char * str2);

  /* **********************************************
   *
   * @Nom : CONSOLE_start
   * @Definicio : Procediment encarregat d'activar la consola.
   * @Arg : In: conf = Configuration amb la configuració de la consola.
   * @Ret : void
   *
   ************************************************/
   void CONSOLE_start(Configuration configuration, int socket);

#endif
