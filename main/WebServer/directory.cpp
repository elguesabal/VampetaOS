/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
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
 * @return RETORNA true CASO O DIRETORIO /VampetaOS/WebServer OU SEJA CRIADO COM SUCESSO
 * @return RETORNA false SE EXISTIR UM ARQUIVO COM O NOME /VampetaOS/WebServer
 * @return RETORNA false SE O DIRETORIO /VampetaOS/WebServer NAO EXISTE A FALHE NA CRIACAO
*/
bool	WebServer::check_dir(void) {
	if (!Sd::exist_dir("/WebServer")) {
		if (Sd::exist_file("/WebServer")) {
			printf("/VampetaOS/WebServer must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/WebServer")) {
			printf("Failed to create /VampetaOS/WebServer: %s\n", strerror(errno));
			return (false);
		}
	}
	return (true);
}