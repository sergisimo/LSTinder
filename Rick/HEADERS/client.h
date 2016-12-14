/********************************************************************
*
* @Arxiu : client.h
* @Finalitat : Capçalera de les funcions que permetran establir nova conexio amb LSTinder.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 8 Novembre del 2016
*
******************************************************************** */
#ifndef _CLIENT_H_
  #define _CLIENT_H_

  /**** LLIBRERIES DE SISTEMA ****/

  /**** LLIBRERIES PROPIES ****/
  #include "command.h"
  #include "signals.h"


  /**** CONSTANTS ****/
  #define CLIENT_CONNECTION_REQUEST "CONSV"
  #define CLIENT_CONECTION_OK_RESPONSE "CONOK"

  #define CLIENT_OK_CONNECTION_MESSAGE "Rick >> Connexio amb LsTinder establerta correctament.\n\n"
  #define CLIENT_KO_CONNECTION_MESSAGE "Rick >> No s'ha pogut connectar amb el servidor LSTinder!\n\n"

  #define CLIENT_SAVING_INFORMATION_MESSAGE "Rick >> Guardant informació Mortys.\n\n"
  #define CLIENT_NO_MORTY_AVIABLE "No hi ha cap Morty a la xarxa!\n\n"

  /**** CAPÇALERES ****/
  void* CLIENT_updateThread(void * aux);

  void CLIENT_updateList();

  void CLIENT_connect(Configuration * configuration);

#endif
