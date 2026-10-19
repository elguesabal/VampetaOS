/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/response.cpp                                                   |
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
	// httpd_resp_set_type(req, content_type);
	// return (httpd_resp_send(req, reinterpret_cast<const char *>(start), end - start));

	if (req == nullptr || start == nullptr || end == nullptr || end < start) return (ESP_ERR_INVALID_ARG);
    esp_err_t err = httpd_resp_set_type(req, content_type);
    if (err != ESP_OK) return (err);
	return (httpd_resp_send(req, reinterpret_cast<const char *>(start), (end - 1) - start)); // ESTUDAR MELHOR SE EU DEVERIA SUBTRAIR 1 DO ENDERECO FINAL DO ARQUIVO
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