/********************************************************************
*
* @Arxiu : console.h
* @Finalitat : Capçalera de les funcions que permetran gestionar la consola incorporada en el programa Morty.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 22 d'Octubre del 2016
*
******************************************************************** */
#ifndef _FITXERS_H_
  #define _FITXERS_H_

  /**** LLIBRERIES DE SISTEMA ****/

  /**** LLIBRERIES PROPIES ****/

  /**** CONSTANTS ****/
  #define CONSOLE_SEARCH  "search"
  #define CONSOLE_EXIT    "exit"

  /**** CAPÇALERES ****/

  /* **********************************************
   *
   * @Nom : CONSOLE_handleCommand
   * @Definicio : Procediment encarregat de cridar a la funció necessaria segons la comanda que entri l'usuari.
   * @Arg : In: command = cadena de caràcters amb la comanda que ha entrat l'usuari, amb tots els arguments.
   * @Ret : void
   *
   ************************************************/
  void CONSOLE_handleCommand(char * command);

  /* **********************************************
   *
   * @Nom : CONSOLE_handleSystemCommand
   * @Definicio : Procediment encarregat de tractar i realitzar una crida al sistema linux.
   * @Arg : In: command = cadena de caràcters amb la comanda de Linux a realitzar, amb tots els arguments.
   * @Ret : void
   *
   ************************************************/
  void CONSOLE_handleSystemCommand (char * command);

#endif
