/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/route.cpp                                                      |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  register_route                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief REGISTRA UMA ROTA NA PORTA ESPECIFICADA
 * @return RETORNA true EM CASO DA ROTA SEJA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA false CASO httpd_register_uri_handler FALHE
*/
bool	WebServer::register_route(uint16_t port, const char *url, esp_err_t (*handler)(httpd_req_t *)) {
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server == WebServer::servers.end()) {
		printf("This door is not in use.\n");
		return (false);
	}
	httpd_uri_t uri = {};
	uri.uri = url;
	uri.method = HTTP_GET; // EU DEVERIA RECEBER ISSO COMO ARGUMENTO
	uri.handler = handler;
	uri.user_ctx = NULL;
	esp_err_t ret = httpd_register_uri_handler(server->second, &uri);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		// WebServer::close_port(port); // DEVO ADICIONAR ISSO PARA EVITAR VERIFICACOES?
		return (false);
	}
	return (true);
}