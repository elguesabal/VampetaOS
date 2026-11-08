/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/response_ws.cpp                                                |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  send_text_ws                                                              |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief ENVIA UM TEXTO PARA UMA CONEXAO DO WEBSOCKET
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