/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/terminal.cpp                                                   |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |                                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO COM UM ARQUIVO DA MEMORIA FLASH
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_file_flash(httpd_req_t *req, const char *content_type, const uint8_t *start, const uint8_t *end) {
	httpd_resp_set_type(req, content_type);
	return (httpd_resp_send(req, reinterpret_cast<const char *>(start), end - start));
}

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO HTTP COM UM TEXTO SIMPLES
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_text(httpd_req_t *req, const char *text) {
	httpd_resp_set_type(req, "text/plain; charset=UTF-8");
	return (httpd_resp_send(req, text, HTTPD_RESP_USE_STRLEN));
}

// PQ ESSE ARQUIVO SE CHAMA "terminal.cpp"? DEVERIA SE CHAR "res.cpp" OU "response.cpp"