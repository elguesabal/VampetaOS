/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/webserver.cpp                                                  |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_webserver                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

std::map<uint16_t, httpd_handle_t> WebServer::servers;

/**
 * @author elguesabal
 * @brief INICIA O WEBSERVER
 * @return RETORNA true EM CASO DO WEBSERVER INICIADO COM SUCESSO
 * @return RETORNA false CASO check_dir FALHE
 * @return RETORNA false CASO open_port FALHE
 * @return RETORNA false CASO register_routes FALHE
*/
bool	WebServer::init_webserver(void) {
	if (!WebServer::check_dir()) return (false); // ACHO Q NAO VAI PRECISAR ARMAZENAR NADA EM /VampetaOS/WebServer/
	printf("WebServer: OK\n");
	return (true);
}