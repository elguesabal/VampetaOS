/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebTerminal/websocket_shell.cpp                                          |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  connect_ws                                                                |
  |  frame_ws                                                                  |
  |  disconnect_ws                                                             |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE SERA DISPARADO CADA VEZ QUE UM WEBSOCKET E CONECTADO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA connect.error CASO build_websocket_connect FALHE
 * @return RETORNA ESP_ERR_NO_MEM CASO OCORRA UMA FALHA NA ALOCACAO DE MEMORIA DO OBJETO Shell
 * @return RETORNA ESP_FAIL CASO OCORRA UMA FALHA NA CRIACAO DA TASK OU QUEUE DO Shell
 * @return RETORNA ESP_FAIL CASO OCORRA UMA FALHA AO REGISTRAR A NOVA SESSAO NO MAP sessions
 * @return RETORNA ESP_ERR_NO_MEM EM CASO DE FALHA DE ALOCACAO DA MEMORIA DE ascii_art
 * @return RETORNA ret CASO WebServer::send_text_ws FALHE
*/
esp_err_t	WebTerminal::connect_ws(httpd_req_t *req) {
	WebSocket_connect connect = WebServer::build_websocket_connect(req);
	if (connect.error != ESP_OK) return (connect.error);
// MUTEX???
	Shell *shell = new (std::nothrow) Shell(connect);
	if (shell == nullptr) return (ESP_ERR_NO_MEM);
	if (!shell->is_initialized()) {
		delete shell;
		return (ESP_FAIL);
	}
	std::pair<std::map<int, Shell*>::iterator, bool> result = WebTerminal::sessions.insert(std::make_pair(connect.fd, shell));
	if (!result.second) {
		delete shell;
		return (ESP_FAIL);
	}
// MUTEX???
	extern const uint8_t ascii_art_start[] asm("_binary_ascii_art_start");
	extern const uint8_t ascii_art_end[] asm("_binary_ascii_art_end");
	size_t len = ascii_art_end - ascii_art_start;
	char *ascii_art = new (std::nothrow) char[len + 1];
	if (ascii_art == nullptr) {
		WebTerminal::sessions.erase(connect.fd);
		delete shell;
		return (ESP_ERR_NO_MEM);
	}
	memcpy(ascii_art, ascii_art_start, len);
	ascii_art[len] = '\0';
	esp_err_t ret = WebServer::send_text_ws(req, ascii_art);
	delete[] ascii_art;
	if (ret != ESP_OK) {
		WebTerminal::sessions.erase(connect.fd);
		delete shell;
		return (ret);
	}
	return (ret);
}

/**
 * @author elguesabal
 * @brief METODO DE CONTROLE DO WEBSOCKET 
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA ESP_OK EM CASO DE SUCESSP
 * @return RETORNA frame.error CASO build_websocket_frame FALHE
 * @return RETORNA ESP_ERR_NOT_FOUND CASO O FILE DESCRIPTION NAO ESTEJA ABERTO DENTRO DE WebTerminal::sessions
*/
esp_err_t	WebTerminal::frame_ws(httpd_req_t *req) {
	WebSocket_frame frame = WebServer::build_websocket_frame(req);
	if (frame.error != ESP_OK) return (frame.error);
	std::map<int, Shell*>::iterator it = WebTerminal::sessions.find(frame.fd);
	if (it == WebTerminal::sessions.end()) return (ESP_ERR_NOT_FOUND);
	it->second->input_shell(frame.payload.c_str());
	return (ESP_OK);
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
	if (event_data == nullptr) return;
	int fd = *(int *)event_data;
	if (fd < 0) return;
	std::map<int, Shell*>::iterator session = WebTerminal::sessions.find(fd);
	if (session == WebTerminal::sessions.end()) return;
	delete session->second;
	WebTerminal::sessions.erase(session);
}