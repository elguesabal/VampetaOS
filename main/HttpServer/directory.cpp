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
 * @return RETORNA true CASO O DIRETORIO /VampetaOS/HttpServer OU SEJA CRIADO COM SUCESSO
 * @return RETORNA false SE EXISTIR UM ARQUIVO COM O NOME /VampetaOS/HttpServer
 * @return RETORNA false SE O DIRETORIO /VampetaOS/HttpServer NAO EXISTE A FALHE NA CRIACAO
*/
bool	HttpServer::check_dir(void) {
	if (!Sd::exist_dir("/HttpServer")) {
		if (Sd::exist_file("/HttpServer")) {
			printf("/VampetaOS/HttpServer must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/HttpServer")) {
			printf("Failed to create /VampetaOS/HttpServer: %s\n", strerror(errno));
			return (false);
		}
	}
	return (true);
}