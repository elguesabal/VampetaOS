/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/response_ws.cpp                                                |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  send_text_ws                                                              |
  |  send_text_ws_fd                                                           |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief ENVIA UM TEXTO PARA UMA CONEXAO DO WEBSOCKET
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param text TEXTO QUE SERA ENVIADO COMO RESPOSTA
 * @return RETORNA ESP_ERR_INVALID_ARG EM CASO req SER nullptr
 * @return RETORNA ESP_ERR_INVALID_ARG EM CASO text SER nullptr
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_text_ws(httpd_req_t *req, const char *text) {
	if (req == nullptr || text == nullptr) return (ESP_ERR_INVALID_ARG);
	httpd_ws_frame_t frame = {};
	frame.type = HTTPD_WS_TYPE_TEXT;
	frame.payload = reinterpret_cast<uint8_t *>(const_cast<char *>(text));
	frame.len = strlen(text);
	return (httpd_ws_send_frame(req, &frame));
}

/**
 * @author elguesabal
 * @brief ENVIA UM TEXTO PARA UMA CONEXAO DO WEBSOCKET USANDO A PORTA E O FILE DESCRIPTION
 * @param port PORTA DA CONEXAO
 * @param fd FILE DESCRIPTION DA CONEXAO
 * @param text TEXTO QUE SERA ENVIADO COMO RESPOSTA
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
 * @return RETORNA ESP_ERR_INVALID_ARG EM CASO text SER nullptr
 * @return RETORNA ESP_ERR_NOT_FOUND EM CASO DA PORTA NAO ESTEJA ABERTA
*/
esp_err_t	WebServer::send_text_ws_fd(uint16_t port, int fd, const char *text) {
	if (text == nullptr) return (ESP_ERR_INVALID_ARG);
	std::map<uint16_t, httpd_handle_t>::iterator server = WebServer::servers.find(port);
	if (server == WebServer::servers.end()) return (ESP_ERR_NOT_FOUND);
	httpd_ws_frame_t frame = {};
	frame.type = HTTPD_WS_TYPE_TEXT;
	frame.payload = (uint8_t *)text;
	frame.len = strlen(text);
	return (httpd_ws_send_frame_async(server->second, fd, &frame));
}