/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/response.cpp                                                   |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  send_file_flash                                                           |
  |  send_text                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO COM UM ARQUIVO DA MEMORIA FLASH
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param content_type TIPO DE CONTEUDO (MIME) DO ARQUIVO QUE SERA ENVIADO NA RESPOSTA HTTP
 * @param start PONTEIRO PARA O INICIO DOS DADOS DO ARQUIVO ARMAZENADO NA MEMORIA FLASH
 * @param end PONTEIRO PARA O FINAL DOS DADOS DO ARQUIVO ARMAZENADO NA MEMORIA FLASH
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_file_flash(httpd_req_t *req, const char *content_type, const uint8_t *start, const uint8_t *end) {
	if (req == nullptr || start == nullptr || end == nullptr || end < start) return (ESP_ERR_INVALID_ARG);
	esp_err_t err = httpd_resp_set_type(req, content_type);
	if (err != ESP_OK) return (err);
	return (httpd_resp_send(req, reinterpret_cast<const char *>(start), (end - 1) - start));
}

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO HTTP COM UM TEXTO SIMPLES
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param text TEXTO QUE SERA ENVIADO AO CLIENTE COMO RESPOSTA A REQUISICAO HTTP
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_text(httpd_req_t *req, const char *text) {
	httpd_resp_set_type(req, "text/plain; charset=UTF-8");
	return (httpd_resp_send(req, text, HTTPD_RESP_USE_STRLEN));
}