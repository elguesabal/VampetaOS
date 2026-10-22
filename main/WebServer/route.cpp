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
  |  unregister_route                                                          |
  |  get                                                                       |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief REGISTRA UMA ROTA NA PORTA ESPECIFICADA
 * @return RETORNA true EM CASO DA ROTA SEJA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA 
 * @return RETORNA false CASO httpd_register_uri_handler FALHE
*/
bool	WebServer::register_route(uint16_t port, httpd_method_t method, const char *url, esp_err_t (*handler)(httpd_req_t *)) {
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server == WebServer::servers.end()) {
		printf("This door is not in use.\n");
		return (false);
	}
	httpd_uri_t uri = {};
	uri.uri = url;
	uri.method = method;
	uri.handler = handler;
	uri.user_ctx = NULL;
	esp_err_t ret = httpd_register_uri_handler(server->second, &uri);
	if (ret == ESP_ERR_HTTPD_HANDLER_EXISTS) {
		if (!WebServer::unregister_route(port, method, url)) return (false);
		ret = httpd_register_uri_handler(server->second, &uri);
	}
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		// WebServer::close_port(port); // DEVO ADICIONAR ISSO PARA EVITAR VERIFICACOES?
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief REMOVE O REGISTRO DE UMA ROTA NA PORTA ESPECIFICADA
 * @return RETORNA true EM CASO DO REGISTRO DA ROTA SEJA REMOVIDA COM SUCESSO
 * @return RETORNA true CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA false CASO httpd_unregister_uri_handler FALHE
*/
bool	WebServer::unregister_route(uint16_t port, httpd_method_t method, const char *url) {
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server == WebServer::servers.end()) {
		printf("This door is not in use.\n");
		return (true);
	}
	esp_err_t ret = httpd_unregister_uri_handler(server->second, url, method);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}

bool	WebServer::get(uint16_t port, const char *url, esp_err_t (*handler)(httpd_req_t *)) {
	if (!WebServer::register_route(port, HTTP_GET, url, handler)) return (false);
	return (true);
}
// bool	WebServer::post()
// bool	WebServer::put()
// bool	WebServer::delete()
// bool	WebServer::patch()
// bool	WebServer::head()
// bool	WebServer::options()
// bool	WebServer::trace()
// bool	WebServer::connect()