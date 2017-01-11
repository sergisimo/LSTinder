/********************************************************************
*
* @Arxiu : command.h
* @Finalitat : Capçaleres de les funcions que conformen el TAD comanda.
* @Autors : Esteve Genovard Ferriol - ls30742 & Sergi Simó Bosquet - ls30685
* @Data Creació: 12 de Desembre del 2016
*
******************************************************************** */
#ifndef _COMMAND_H_
	#define _COMMAND_H_

  //Llibreries pròpies
  #include "signals.h"

  //Constants
  #define COMMAND_SIZE 115
  #define COMMAND_TYPE_MAX 5
  #define COMMAND_INFO_MAX 15

	#define COMMAND_TYPE_MORTY_CONNECTION "CONCL"
	#define COMMAND_TYPE_MORTY_DISCONNECTION "DESC"
	#define COMMAND_TYPE_MORTY_NEXT "NMORT"
	#define COMMAND_TYPE_MORTY_LIKE "NLIKE"

	#define COMMAND_INFO_MORTY_CONNECTION "INFO"
	#define COMMAND_INFO_MORTY_CONNECTION_OK "OK_CONEX"
	#define COMMAND_INFO_MORTY_CONNECTION_KO "KO_CONEX"
	#define COMMAND_INFO_MORTY_DISCONNECTION_OK "OK_DESC"
	#define COMMAND_INFO_MORTY_DISCONNECTION_KO "KO_DESC"
	#define COMMAND_INFO_MORTY_NEXT "NEW_MORTY"
	#define COMMAND_INFO_MORTY_NEXT_NO "NO_MORTY"
	#define COMMAND_INFO_MORTY_LIKE "NEW_LIKE"

	#define COMMAND_TYPE_LSTINDER_CONNECTION_SEND "CONSV"
	#define COMMAND_TYPE_LSTINDER_CONNECTION_OK "CONOK"
	#define COMMAND_TYPE_LSTINDER_CONNECTION_KO "CONKO"
	#define COMMAND_TYPE_LSTINDER_CLIENT_SEND "NOUMO"
	#define COMMAND_TYPE_LSTINDER_CLIENT_OK "PETOK"
	#define COMMAND_TYPE_LSTINDER_CLIENT_KO "PETKO"
	#define COMMAND_TYPE_LSTINDER_DELETE_SEND "BORMO"
	#define COMMAND_TYPE_LSTINDER_DELETE_OK "BOROK"
	#define COMMAND_TYPE_LSTINDER_DELETE_KO "BORKO"
	#define COMMAND_TYPE_LSTINDER_USER_SEND "ACTUA"
	#define COMMAND_TYPE_LSTINDER_USER "USER"
	#define COMMAND_TYPE_LSTINDER_USER_FI "FIACT"
	#define COMMAND_TYPE_LSTINDER_MATCH "MATCH"

	#define COMMAND_INFO_LSTINDER_USER "OPCIONAL"


  //Capçaleres
  void COMMAND_create(Command command);

  void COMMAND_setType(Command command, char * type);

  void COMMAND_setInfo(Command command, char * info);

  void COMMAND_setData(Command command, char * data, int firstPosition);

	CommandType COMMAND_getType(Command command);

	CommandInfo COMMAND_getInfo(Command command);

	char * COMMAND_getData(Command command, int start, int final);

	int COMMAND_getPort(Command command);

	void COMMAND_copy(Command dest, Command origin);

#endif
