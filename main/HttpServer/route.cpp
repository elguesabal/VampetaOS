/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /HttpServer/route.cpp                                                     |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  add_get                                                                   |
  |  remove_get                                                                |
  |  add_post                                                                  |
  |  remove_post                                                               |
  |  add_websocket                                                             |
  |  remove_websocket                                                          |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "HttpServer.hpp"

/**
 * @author elguesabal
 * @brief REGISTRA UMA ROTA GET NA PORTA this->port
 * @param path CAMINHO DA URL QUE IDENTIFICA A ROTA
 * @param handle FUNCAO RESPONSAVEL POR PROCESSAR AS REQUISICOES RECEBIDAS PELA ROTA
 * @return RETORNA true EM CASO DA ROTA SEJA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO register_route FALHE
*/
bool	HttpServer::add_get(const char *path, esp_err_t (*handler)(httpd_req_t *)) {
	return (WebServer::register_route_http(this->port, HTTP_GET, path, handler));
}

/**
 * @author elguesabal
 * @brief REMOVE O REGISTRO DE UMA ROTA GET NA PORTA this->port
 * @param path CAMINHO DA URL QUE IDENTIFICA A ROTA A SER REMOVIDA
 * @return RETORNA true EM CASO DO REGISTRO DA ROTA SEJA REMOVIDA COM SUCESSO
 * @return RETORNA true CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA false CASO unregister_route FALHE
*/
bool	HttpServer::remove_get(const char *path) {
	return (WebServer::unregister_route(this->port, HTTP_GET, path));
}

/**
 * @author elguesabal
 * @brief REGISTRA UMA ROTA POST NA PORTA this->port
 * @param path CAMINHO DA URL QUE IDENTIFICA A ROTA
 * @param handle FUNCAO RESPONSAVEL POR PROCESSAR AS REQUISICOES RECEBIDAS PELA ROTA
 * @return RETORNA true EM CASO DA ROTA SEJA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO register_route FALHE
*/
bool	HttpServer::add_post(const char *path, esp_err_t (*handler)(httpd_req_t *)) {
	return (WebServer::register_route_http(this->port, HTTP_POST, path, handler));
}

/**
 * @author elguesabal
 * @brief REMOVE O REGISTRO DE UMA ROTA POST NA PORTA this->port
 * @param path CAMINHO DA URL QUE IDENTIFICA A ROTA A SER REMOVIDA
 * @return RETORNA true EM CASO DO REGISTRO DA ROTA SEJA REMOVIDA COM SUCESSO
 * @return RETORNA true CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA false CASO unregister_route FALHE
*/
bool	HttpServer::remove_post(const char *path) {
	return (WebServer::unregister_route(this->port, HTTP_POST, path));
}

/**
 * @author elguesabal
 * @brief REGISTRA UMA ROTA WEBSOCKET NA PORTA this->port
 * @param path CAMINHO DA URL QUE IDENTIFICA A ROTA
 * @param handle FUNCAO RESPONSAVEL POR PROCESSAR AS REQUISICOES RECEBIDAS PELA ROTA
 * @return RETORNA true EM CASO DA ROTA SEJA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO register_route_websocket FALHE
*/
bool	HttpServer::add_websocket(const char *path, esp_err_t (*handler)(httpd_req_t *)) {
	return (WebServer::register_route_websocket(this->port, path, handler));
}

/**
 * @author elguesabal
 * @brief REMOVE O REGISTRO DE UMA ROTA WEBSOCKET NA PORTA this->port
 * @param path CAMINHO DA URL QUE IDENTIFICA A ROTA A SER REMOVIDA
 * @return RETORNA true EM CASO DO REGISTRO DA ROTA SEJA REMOVIDA COM SUCESSO
 * @return RETORNA true CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA false CASO unregister_route FALHE
*/
bool	HttpServer::remove_websocket(const char *path) {
	return (WebServer::unregister_route(this->port, HTTP_GET, path));
}