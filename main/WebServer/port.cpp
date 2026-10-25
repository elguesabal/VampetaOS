/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/port.cpp                                                       |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  open_port                                                                 |
  |  close_port                                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief INICIA UMA PORTA
 * @param port PORTA QUE SERA UTILIZADA PARA ESCUTAR REQUISICOES
 * @return RETORNA true EM CASO DA PORTA SEJA INICIADA COM SUCESSO
 * @return RETORNA false CASO A PORTA JA ESTEJA OCUPADA
 * @return RETORNA false CASO httpd_start FALHE
*/
bool	WebServer::open_port(uint16_t port) {
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server != WebServer::servers.end()) {
		printf("Port already in use\n");
		return (false);
	}
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	config.server_port = port;
    config.ctrl_port = port;
	httpd_handle_t handle = NULL;
	esp_err_t ret = httpd_start(&handle, &config);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	WebServer::servers.emplace(port, handle);
	return (true);
}

/**
 * @author elguesabal
 * @brief FECHA UMA PORTA
 * @param port PORTA QUE VAI SER FECHADA
 * @return RETORNA true EM CASO DA PORTA SEJA FECHADA COM SUCESSO
 * @return RETORNA true CASO A PORTA NAO ESTEJA SENDO USADA
 * @return RETORNA false CASO httpd_stop FALHE
*/
bool	WebServer::close_port(uint16_t port) {
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server == WebServer::servers.end()) {
		printf("This door is not in use.\n");
		return (true);
	}
	esp_err_t ret = httpd_stop(server->second);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	WebServer::servers.erase(server);
	return (true);
}