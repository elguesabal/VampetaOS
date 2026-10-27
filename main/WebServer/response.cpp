/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/response.cpp                                                   |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  status                                                                    |
  |  send_status                                                               |
  |  send_file_flash                                                           |
  |  send_text                                                                 |
  |  send_json                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief IDENTIFICA O CODIGO E RETORNA O CODIGO APROPRIADO EM STRING
 * @param status CODIGO DE STATUS QUE SERA TRANSFORMADO EM STRING
 * @return RETORNA UMA STRING EM CASO DO CODIGO SEM VALIDO
 * @return RETORNA NULL EM CASO DO CODIGO SEM INVALIDO
*/
const char	*WebServer::status(const uint16_t code) {
	switch (code) {
		case 200: return ("200 OK");
		case 201: return ("201 Created");
		case 204: return ("204 No Content");
		case 400: return ("400 Bad Request");
		case 401: return ("401 Unauthorized");
		case 403: return ("403 Forbidden");
		case 404: return ("404 Not Found");
		case 405: return ("405 Method Not Allowed");
		case 409: return ("409 Conflict");
		case 500: return ("500 Internal Server Error");
		case 503: return ("503 Service Unavailable");
		default: return (NULL);
	}
}

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO APENAS COM O STATUS CODE
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param status CODIGO DE STATUS QUE SERA ENVIADO
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_status(httpd_req_t *req, const uint16_t status) {
	if (req == nullptr) return (ESP_ERR_INVALID_ARG);
	const char *code = WebServer::status(status);
	if (code == NULL) return (ESP_ERR_INVALID_ARG);
	esp_err_t err = httpd_resp_set_status(req, code);
	if (err != ESP_OK) return (err);
	return (httpd_resp_send(req, NULL, 0));
}

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO COM UM ARQUIVO DA MEMORIA FLASH
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param status CODIGO DE STATUS QUE SERA ENVIADO
 * @param content_type TIPO DE CONTEUDO (MIME) DO ARQUIVO QUE SERA ENVIADO NA RESPOSTA HTTP
 * @param start PONTEIRO PARA O INICIO DOS DADOS DO ARQUIVO ARMAZENADO NA MEMORIA FLASH
 * @param end PONTEIRO PARA O FINAL DOS DADOS DO ARQUIVO ARMAZENADO NA MEMORIA FLASH
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_file_flash(httpd_req_t *req, const uint16_t status, const char *content_type, const uint8_t *start, const uint8_t *end) {
	if (req == nullptr || status == 204 || start == nullptr || content_type == nullptr || end == nullptr || end < start) return (ESP_ERR_INVALID_ARG);
	const char *code = WebServer::status(status);
	if (code == NULL) return (ESP_ERR_INVALID_ARG);
	esp_err_t err = httpd_resp_set_status(req, code);
	if (err != ESP_OK) return (err);
	err = httpd_resp_set_type(req, content_type);
	if (err != ESP_OK) return (err);
	return (httpd_resp_send(req, reinterpret_cast<const char *>(start), (end - 1) - start));
}

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO HTTP COM UM TEXTO SIMPLES
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param status CODIGO DE STATUS QUE SERA ENVIADO
 * @param text TEXTO QUE SERA ENVIADO AO CLIENTE COMO RESPOSTA A REQUISICAO HTTP
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_text(httpd_req_t *req, const uint16_t status, const char *text) {
	if (req == nullptr || status == 204 || text == nullptr) return (ESP_ERR_INVALID_ARG);
	const char *code = WebServer::status(status);
	if (code == NULL) return (ESP_ERR_INVALID_ARG);
	esp_err_t err = httpd_resp_set_status(req, code);
	if (err != ESP_OK) return (err);
	err = httpd_resp_set_type(req, "text/plain; charset=UTF-8");
	if (err != ESP_OK) return (err);
	return (httpd_resp_send(req, text, HTTPD_RESP_USE_STRLEN));
}

/**
 * @author elguesabal
 * @brief RESPONDE A REQUISICAO HTTP COM UM JSON
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param status CODIGO DE STATUS QUE SERA ENVIADO
 * @param json JSON QUE SERA ENVIADO AO CLIENTE COMO RESPOSTA A REQUISICAO HTTP
 * @return RETORNA ESP_OK EM CASO DE SUCESSO
*/
esp_err_t	WebServer::send_json(httpd_req_t *req, const uint16_t status, const char *json) {
	if (req == nullptr || status == 204 || json == nullptr) return (ESP_ERR_INVALID_ARG);
	const char *code = WebServer::status(status);
	if (code == NULL) return (ESP_ERR_INVALID_ARG);
	esp_err_t err = httpd_resp_set_status(req, code);
	if (err != ESP_OK) return (err);
	err = httpd_resp_set_type(req, "application/json; charset=UTF-8");
	if (err != ESP_OK) return (err);
	return (httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN));
}