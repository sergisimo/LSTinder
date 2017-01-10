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

	#define COMMAND_TYPE_RICK_MATCH "MATCH"
	#define COMMAND_TYPE_RICK_CONNECTION "CONCL"
	#define COMMAND_TYPE_RICK_DISCONNECTION "DESC"
	#define COMMAND_TYPE_RICK_NEXT "NMORT"
	#define COMMAND_TYPE_RICK_LIKE "NLIKE"

	#define COMMAND_INFO_RICK_CONNECTION "INFO"
	#define COMMAND_INFO_RICK_CONNECTION_OK "OK_CONEX"
	#define COMMAND_INFO_RICK_CONNECTION_KO "KO_CONEX"
	#define COMMAND_INFO_RICK_DISCONNECTION_OK "OK_DESC"
	#define COMMAND_INFO_RICK_DISCONNECTION_KO "KO_DESC"
	#define COMMAND_INFO_RICK_NEXT "NEW_MORTY"
	#define COMMAND_INFO_RICK_NEXT_NO "NO_MORTY"
	#define COMMAND_INFO_RICK_LIKE "NEW_LIKE"

	#define COMMAND_TYPE_MORTY_XAT "MISSA"

	#define COMMAND_INFO_MORTY_XAT_EXIT "EXIT"

  //Capçaleres
  void COMMAND_create(Command command);

  void COMMAND_setType(Command command, char * type);

  void COMMAND_setInfo(Command command, char * info);

  void COMMAND_setData(Command command, char * data, int firstPosition);

	CommandType COMMAND_getType(Command command);

	CommandInfo COMMAND_getInfo(Command command);

	int COMMAND_getPort(Command command);

	char * COMMAND_getData(Command command, int start, int final);

#endif
