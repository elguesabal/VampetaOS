/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
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

// ???
esp_err_t	WebTerminal::index_html(httpd_req_t *req) {
	extern const uint8_t index_html_start[] asm("_binary_index_html_start");
	extern const uint8_t index_html_end[] asm("_binary_index_html_end");
	return (WebServer::send_file_flash(req, "text/html; charset=UTF-8", index_html_start, index_html_end));
}

// ???
esp_err_t	WebTerminal::style_css(httpd_req_t *req) {
	extern const uint8_t style_css_start[] asm("_binary_style_css_start");
	extern const uint8_t style_css_end[] asm("_binary_style_css_end");

// const size_t len = style_css_end - style_css_start;
// printf("Conteudo do arquivo:\n");
// printf("%.*s\n", static_cast<int>(len), reinterpret_cast<const char *>(style_css_start));

	return (WebServer::send_file_flash(req, "text/css; charset=UTF-8", style_css_start, style_css_end));
}

// ???
esp_err_t	WebTerminal::print_js(httpd_req_t *req) {
	extern const uint8_t print_js_start[] asm("_binary_print_js_start");
	extern const uint8_t print_js_end[] asm("_binary_print_js_end");

// const size_t len = print_js_end - print_js_start;
// ESP_LOGI("WEB", "Tamanho do arquivo: %u", static_cast<unsigned>(len));
// ESP_LOG_BUFFER_HEX("WEB", print_js_end - (len < 16 ? len : 16), len < 16 ? len : 16);

	return (WebServer::send_file_flash(req, "text/javascript; charset=UTF-8", print_js_start, print_js_end));
}

// ???
esp_err_t	WebTerminal::test(httpd_req_t *req) {
	return (WebServer::send_text(req, "VampetaOS"));
}
