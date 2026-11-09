/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/directory.cpp                                                  |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  check_dir                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE OS ARQUIVOS NECESSARIOS ESTAO OK
 * @return RETORNA true CASO O DIRETORIO /VampetaOS/webServer OU SEJA CRIADO COM SUCESSO
 * @return RETORNA false SE EXISTIR UM ARQUIVO COM O NOME /VampetaOS/webServer
 * @return RETORNA false SE O DIRETORIO /VampetaOS/webServer NAO EXISTE A FALHE NA CRIACAO
*/
bool	WebServer::check_dir(void) {
	if (!Sd::exist_dir("/webServer")) {
		if (Sd::exist_file("/webServer")) {
			printf("/VampetaOS/webServer must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/webServer")) {
			printf("Failed to create /VampetaOS/webServer: %s\n", strerror(errno));
			return (false);
		}
	}
	return (true);
}