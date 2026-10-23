/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /HttpServer/httpserver.cpp                                                |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |                                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "HttpServer.hpp"

std::map<uint16_t, httpd_handle_t> HttpServer::servers;

/**
 * @author elguesabal
 * @brief INICIA O HTTPSERVER
 * @return RETORNA true EM CASO DO WEBSERVER INICIADO COM SUCESSO
 * @return RETORNA false CASO check_dir FALHE
 * @return RETORNA false CASO open_port FALHE
 * @return RETORNA false CASO register_routes FALHE
*/
bool	HttpServer::init_httpserver(void) {
	if (!HttpServer::check_dir()) return (false); // ACHO Q NAO VAI PRECISAR ARMAZENAR NADA EM /VampetaOS/HttpServer/
	printf("HttpServer: OK\n");
	return (true);
}

HttpServer::HttpServer(uint16_t port) {

}

HttpServer::~HttpServer(void) {
	
}