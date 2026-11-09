/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /HttpServer/directory.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  check_dir                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "HttpServer.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE OS ARQUIVOS NECESSARIOS ESTAO OK
 * @return RETORNA true CASO O DIRETORIO /VampetaOS/httpServer OU SEJA CRIADO COM SUCESSO
 * @return RETORNA false SE EXISTIR UM ARQUIVO COM O NOME /VampetaOS/httpServer
 * @return RETORNA false SE O DIRETORIO /VampetaOS/httpServer NAO EXISTE A FALHE NA CRIACAO
*/
bool	HttpServer::check_dir(void) {
	if (!Sd::exist_dir("/httpServer")) {
		if (Sd::exist_file("/httpServer")) {
			printf("/VampetaOS/httpServer must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/httpServer")) {
			printf("Failed to create /VampetaOS/httpServer: %s\n", strerror(errno));
			return (false);
		}
	}
	return (true);
}