/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/route.cpp                                                      |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  register_routes                                                           |
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
bool	WebServer::register_routes(uint16_t port, const char *url) {
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server == WebServer::servers.end()) {
		printf("This door is not in use.\n");
		return (false);
	}
	httpd_uri_t uri = {};
	uri.uri = url;
	uri.method = HTTP_GET;
	uri.handler = test_html;
	uri.user_ctx = NULL;
	esp_err_t ret = httpd_register_uri_handler(server->second, &uri);
	if (ret != ESP_OK) {
		printf("register route: %s\n", esp_err_to_name(ret));
		// WebServer::close_port(port); ???
		return (false);
	}
	return (true);
}