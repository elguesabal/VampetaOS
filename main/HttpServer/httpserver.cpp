/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /HttpServer/httpserver.cpp                                                |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_httpserver                                                           |
  |  HttpServer                                                                |
  |  ~HttpServer                                                               |
  |  is_valid                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "HttpServer.hpp"

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

/**
 * @author elguesabal
 * @brief CONSTRUTOR DA CLASSE
 * @param port PORTA QUE SERA UTILIZADA PARA ESCUTAR REQUISICOES
*/
HttpServer::HttpServer(uint16_t port) : port(0), server(NULL) {
	if (!WebServer::open_port(port)) return;
	this->port = port;
	this->server = WebServer::get_server(port);
}

/**
 * @author elguesabal
 * @brief DESTRUTOR DA CLASSE
*/
HttpServer::~HttpServer(void) {
	if (this->server == NULL) return;
	if (!WebServer::close_port(this->port)) printf("Failed to close port %u\n", this->port);
}

/**
 * @author elguesabal
 * @brief METODO CRIADO PARA VERIFICAR SE A INSTANCIA ESTA VALIDA
*/
bool HttpServer::is_valid(void) const {
	return (this->server != NULL);
}