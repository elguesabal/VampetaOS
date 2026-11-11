/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebTerminal/routes.cpp                                                   |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  index_html                                                                |
  |  style_css                                                                 |
  |  variables_js                                                              |
  |  connection_js                                                             |
  |  events_js                                                                 |
  |  keys_js                                                                   |
  |  print_js                                                                  |
  |  connect_ws                                                                |
  |  webterminal                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/index.html
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::index_html(httpd_req_t *req) {
	extern const uint8_t index_html_start[] asm("_binary_index_html_start");
	extern const uint8_t index_html_end[] asm("_binary_index_html_end");
	return (WebServer::send_file_flash_http(req, 200, "text/html; charset=UTF-8", index_html_start, index_html_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /css/style.css
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/css/style.css
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::style_css(httpd_req_t *req) {
	extern const uint8_t style_css_start[] asm("_binary_style_css_start");
	extern const uint8_t style_css_end[] asm("_binary_style_css_end");
	return (WebServer::send_file_flash_http(req, 200, "text/css; charset=UTF-8", style_css_start, style_css_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/variables.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/variables.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::variables_js(httpd_req_t *req) {
	extern const uint8_t variables_js_start[] asm("_binary_variables_js_start");
	extern const uint8_t variables_js_end[] asm("_binary_variables_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", variables_js_start, variables_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/connection.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/connection.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::connection_js(httpd_req_t *req) {
	extern const uint8_t connection_js_start[] asm("_binary_connection_js_start");
	extern const uint8_t connection_js_end[] asm("_binary_connection_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", connection_js_start, connection_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/events.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/events.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::events_js(httpd_req_t *req) {
	extern const uint8_t events_js_start[] asm("_binary_events_js_start");
	extern const uint8_t events_js_end[] asm("_binary_events_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", events_js_start, events_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/keys.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/keys.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::keys_js(httpd_req_t *req) {
	extern const uint8_t keys_js_start[] asm("_binary_keys_js_start");
	extern const uint8_t keys_js_end[] asm("_binary_keys_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", keys_js_start, keys_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/print.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/print.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::print_js(httpd_req_t *req) {
	extern const uint8_t print_js_start[] asm("_binary_print_js_start");
	extern const uint8_t print_js_end[] asm("_binary_print_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", print_js_start, print_js_end));
}

/**
 * @author elguesabal
 * @brief METODO QUE SERA DISPARADO CADA VEZ QUE UM WEBSOCKET E CONECTADO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA connect.error CASO build_websocket_connect FALHE
 * @return RETORNA ESP_ERR_NO_MEM CASO OCORRA UMA FALHA NA ALOCACAO DE MEMORIA DO OBJETO Shell
 * @return RETORNA ESP_FAIL CASO OCORRA UMA FALHA AO REGISTRAR A NOVA SESSAO NO MAP sessions
 * @return RETORNA ESP_ERR_NO_MEM EM CASO DE FALHA DE ALOCACAO DA MEMORIA DE ascii_art
 * @return RETORNA ret CASO WebServer::send_text_ws FALHE
*/
esp_err_t	WebTerminal::connect_ws(httpd_req_t *req) {
	WebSocket_connect connect = WebServer::build_websocket_connect(req);
	if (connect.error != ESP_OK) return (connect.error);



// MUTEX???
Shell *shell = new (std::nothrow) Shell();
if (shell == NULL) return (ESP_ERR_NO_MEM);
WebTerminal_session session;
session.fd = connect.fd;
session.shell = shell;
std::pair<std::map<int, WebTerminal_session>::iterator, bool> result = WebTerminal::sessions.insert(std::make_pair(connect.fd, session));
if (!result.second) {
    delete shell;
    return (ESP_FAIL);
}



	extern const uint8_t ascii_art_start[] asm("_binary_ascii_art_start");
	extern const uint8_t ascii_art_end[] asm("_binary_ascii_art_end");
	size_t len = ascii_art_end - ascii_art_start;
	char *ascii_art = new (std::nothrow) char[len + 1];
	if (ascii_art == nullptr) return (ESP_ERR_NO_MEM);	// DEVERIA REMOVER O FD DE session???
	memcpy(ascii_art, ascii_art_start, len);
	ascii_art[len] = '\0';
	esp_err_t ret = WebServer::send_text_ws(req, ascii_art);
	delete[] ascii_art;
	return (ret);
}

/**
 * @author elguesabal
 * @brief METODO DE CONTROLE DO WEBSOCKET 
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM UM "VampetaOS"
 * @return RETORNA false CASO httpd_ws_send_frame FALHE
*/
esp_err_t	WebTerminal::input_shell(httpd_req_t *req) {
	WebSocket_frame frame = WebServer::build_websocket_frame(req);
	if (frame.error != ESP_OK) return (frame.error);
	std::string output = Shell::shell(frame.payload);
	esp_err_t ret = WebServer::send_text_ws(req, output.c_str());
	return (ret);
}

/**
 * @author elguesabal
 * @brief METODO DE CONTROLE DE DISCONECT DO WEBSOCKET 
 * @param arg PONTEIRO PARA ARGUMENTOS ADICIONAIS PASSADOS DURANTE O REGISTRO DO EVENT HANDLER
 * @param event_base IDENTIFICADOR DA BASE DO EVENTO RECEBIDO
 * @param event_id IDENTIFICADOR DO EVENTO DISPARADO PELO SERVIDOR HTTP
 * @param event_data PONTEIRO PARA OS DADOS DO EVENTO CONTENDO O FD DA CONEXAO DESCONECTADA
*/
void	WebTerminal::disconnect_ws(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
	(void)arg;
	(void)event_base;
	if (event_id != HTTP_SERVER_EVENT_DISCONNECTED) return;
	int fd = *(int *)event_data;
	if (fd < 0) return;
	std::map<int, WebTerminal_session>::iterator session = WebTerminal::sessions.find(fd);
	if (session == WebTerminal::sessions.end()) return;
	delete session->second.shell;
	WebTerminal::sessions.erase(session);
}