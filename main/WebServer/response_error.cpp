/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/response_error.cpp                                             |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  register_response_error                                                   |
  |  not_found                                                                 |
  |  internal_server_error                                                     |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief REGISTRA OS HANDLERS PADRAO PARA TRATAMENTO DE ERROS HTTP
 * @param server HANDLE DO SERVIDOR HTTP EM QUE OS HANDLERS SERAO REGISTRADOS
 * @return RETORNA true EM CASO DE SUCESSO AO REGISTRAR RESPOSTAS DE ERROS
 * @return RETORNA false CASO httpd_register_err_handler FALHE
 * @return RETORNA false CASO httpd_register_err_handler FALHE
*/
bool	WebServer::register_response_error(httpd_handle_t server) {
	esp_err_t ret = httpd_register_err_handler(server, HTTPD_404_NOT_FOUND, WebServer::not_found);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = httpd_register_err_handler(server, HTTPD_500_INTERNAL_SERVER_ERROR, WebServer::internal_server_error);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DE RESPOSTA EM ERROS 404
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param error CODIGO DO ERRO HTTP QUE SERA TRATADO
 * @return RETORNA CODIGO RETORNADO POR send_file_flash_http
*/
esp_err_t	WebServer::not_found(httpd_req_t *req, httpd_err_code_t error) {
	(void)error;
	extern const uint8_t not_found_html_start[] asm("_binary_not_found_html_start");
	extern const uint8_t not_found_html_end[] asm("_binary_not_found_html_end");
	return (WebServer::send_file_flash_http(req, 404, "text/html", not_found_html_start, not_found_html_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DE RESPOSTA EM ERROS 500
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param error CODIGO DO ERRO HTTP QUE SERA TRATADO
 * @return RETORNA CODIGO RETORNADO POR send_file_flash_http
*/
esp_err_t	WebServer::internal_server_error(httpd_req_t *req, httpd_err_code_t error) {
	(void)error;
	extern const uint8_t internal_server_error_html_start[] asm("_binary_internal_server_error_html_start");
	extern const uint8_t internal_server_error_html_end[] asm("_binary_internal_server_error_html_end");
	return (WebServer::send_file_flash_http(req, 500, "text/html", internal_server_error_html_start, internal_server_error_html_end));
}