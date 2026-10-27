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
  |  print_js                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/index.html
 * @return RETORNA false CASO send_file_flash FALHE
*/
esp_err_t	WebTerminal::index_html(httpd_req_t *req) {
	extern const uint8_t index_html_start[] asm("_binary_index_html_start");
	extern const uint8_t index_html_end[] asm("_binary_index_html_end");
	return (WebServer::send_file_flash(req, 200, "text/html; charset=UTF-8", index_html_start, index_html_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /css/style.css
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/css/style.css
 * @return RETORNA false CASO send_file_flash FALHE
*/
esp_err_t	WebTerminal::style_css(httpd_req_t *req) {
	extern const uint8_t style_css_start[] asm("_binary_style_css_start");
	extern const uint8_t style_css_end[] asm("_binary_style_css_end");
	return (WebServer::send_file_flash(req, 200, "text/css; charset=UTF-8", style_css_start, style_css_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/print.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/print.js
 * @return RETORNA false CASO send_file_flash FALHE
*/
esp_err_t	WebTerminal::print_js(httpd_req_t *req) {
	extern const uint8_t print_js_start[] asm("_binary_print_js_start");
	extern const uint8_t print_js_end[] asm("_binary_print_js_end");
	return (WebServer::send_file_flash(req, 200, "text/javascript; charset=UTF-8", print_js_start, print_js_end));
}