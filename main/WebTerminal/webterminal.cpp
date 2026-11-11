/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebTerminal/webterminal.cpp                                              |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_webterminal                                                          |
  |  init_server                                                               |
  |  init_handler_disconnect_ws                                                |
  |  init_routes                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

HttpServer *WebTerminal::server = NULL;
std::map<int, WebTerminal_session> WebTerminal::sessions;

/**
 * @author elguesabal
 * @brief INICIA O WEBTERMINAL
 * @return RETORNA true EM CASO DO WEBTERMINAL INICIADO COM SUCESSO
 * @return RETORNA false CASO init_server FALHE
 * @return RETORNA false CASO init_routes FALHE
*/
bool	WebTerminal::init_webterminal(void) {
	if (!WebTerminal::init_server()) return (false);
	if (!WebTerminal::init_handler_disconnect_ws()) return (false);
	if (!WebTerminal::init_routes()) return (false);
	printf("WebTerminal: OK\n");
	return (true);
}

/**
 * @author elguesabal
 * @brief INICIA O SERVIDOR INSTANCIANDO O OBJETO E ABRINDO A PORTA
 * @return RETORNA true EM CASO DO SERVIDOR INICIADO COM SUCESSO
 * @return RETORNA false CASO A ALOCACAO DE MEMORIA PARA WebTerminal::server FALHE
 * @return RETORNA false CASO HttpServer FALHE
*/
bool	WebTerminal::init_server(void) {
	WebTerminal::server = new (std::nothrow) HttpServer(PORT);
	if (WebTerminal::server == NULL) return (false);
	if (!WebTerminal::server->is_valid()) {
		delete WebTerminal::server;
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief REGISTRA UM EVENTO PERSONALIZADO DE DEDSCONEXAO DE WEBSOCKET
 * @return RETORNA true EM CASO DO EVENTO REGISTRADO COM SUCESSO
 * @return RETORNA false CASO esp_event_handler_register FALHE
*/
bool	WebTerminal::init_handler_disconnect_ws(void) {
	esp_err_t ret = esp_event_handler_register(ESP_HTTP_SERVER_EVENT, HTTP_SERVER_EVENT_DISCONNECTED, WebTerminal::disconnect_ws, NULL);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief REGISTRA AS ROTAS NECESSARIAS PARA INICIAR O WEBTERMINAL
 * @return RETORNA true EM CASO DAS ROTAS INICIADAS COM SUCESSO
 * @return RETORNA false CASO server->add_get FALHE
 * @return RETORNA false CASO server->add_get FALHE
 * @return RETORNA false CASO server->add_get FALHE
*/
bool	WebTerminal::init_routes(void) {
	if (!server->add_get("/", WebTerminal::index_html)) return (false);
	if (!server->add_get("/css/style.css", WebTerminal::style_css)) return (false);
	if (!server->add_get("/js/variables.js", WebTerminal::variables_js)) return (false);
	if (!server->add_get("/js/connection.js", WebTerminal::connection_js)) return (false);
	if (!server->add_get("/js/events.js", WebTerminal::events_js)) return (false);
	if (!server->add_get("/js/keys.js", WebTerminal::keys_js)) return (false);
	if (!server->add_get("/js/print.js", WebTerminal::print_js)) return (false);
	if (!server->add_websocket("/webterminal", WebTerminal::input_shell, WebTerminal::connect_ws)) return (false);
	return (true);
}