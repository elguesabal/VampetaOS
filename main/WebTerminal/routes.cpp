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
  |  events_js                                                                 |
  |  print_js                                                                  |
  |  webterminal                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/index.html
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::index_html(httpd_req_t *req) {
	extern const uint8_t index_html_start[] asm("_binary_index_html_start");
	extern const uint8_t index_html_end[] asm("_binary_index_html_end");
	return (WebServer::send_file_flash_http(req, 200, "text/html; charset=UTF-8", index_html_start, index_html_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /css/style.css
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/css/style.css
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::style_css(httpd_req_t *req) {
	extern const uint8_t style_css_start[] asm("_binary_style_css_start");
	extern const uint8_t style_css_end[] asm("_binary_style_css_end");
	return (WebServer::send_file_flash_http(req, 200, "text/css; charset=UTF-8", style_css_start, style_css_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/variables.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/variables.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::variables_js(httpd_req_t *req) {
	extern const uint8_t variables_js_start[] asm("_binary_variables_js_start");
	extern const uint8_t variables_js_end[] asm("_binary_variables_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", variables_js_start, variables_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/connection.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/connection.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::connection_js(httpd_req_t *req) {
	// Resquest_http request = WebServer::build_request_http(req);

	// printf("\n========== HTTP REQUEST ==========\n");
	// printf("Valid: %s\n", request.valid ? "true" : "false");
	// printf("Method: %d\n", request.method);
	// printf("Path: %s\n", request.path.c_str());
	// printf("Query: %s\n", request.query.c_str());
	// printf("Body: %s\n", request.body.c_str());
	// printf("Content-Type: %s\n", request.content_type.c_str());
	// printf("Content-Length: %u\n", (unsigned int)request.content_length);
	// printf("==================================\n\n");



	extern const uint8_t connection_js_start[] asm("_binary_connection_js_start");
	extern const uint8_t connection_js_end[] asm("_binary_connection_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", connection_js_start, connection_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/events.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/events.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::events_js(httpd_req_t *req) {
	extern const uint8_t events_js_start[] asm("_binary_events_js_start");
	extern const uint8_t events_js_end[] asm("_binary_events_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", events_js_start, events_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/keys.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/keys.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::keys_js(httpd_req_t *req) {
	extern const uint8_t keys_js_start[] asm("_binary_keys_js_start");
	extern const uint8_t keys_js_end[] asm("_binary_keys_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", keys_js_start, keys_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE RESPOSTA DA ROTA /js/print.js
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM O ARQUIVO /VampetaOS/WebTerminal/src/js/print.js
 * @return RETORNA false CASO send_file_flash_http FALHE
*/
esp_err_t	WebTerminal::print_js(httpd_req_t *req) {
	extern const uint8_t print_js_start[] asm("_binary_print_js_start");
	extern const uint8_t print_js_end[] asm("_binary_print_js_end");
	return (WebServer::send_file_flash_http(req, 200, "text/javascript; charset=UTF-8", print_js_start, print_js_end));
}

/**
 * @author elguesabal
 * @brief METODO DE CONTROLE DO WEBSOCKET 
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DE RESPONDER CORRETAMENTE COM UM "VampetaOS"
 * @return RETORNA false CASO httpd_ws_send_frame FALHE
*/
esp_err_t	WebTerminal::webterminal(httpd_req_t *req) {
// printf("Handler chamado!\n");
	// return (WebServer::send_text_ws(req, "VampetaOS"));


	// printf("Handler chamado!\n");
	// printf("Method: %d\n", req->method);

	// httpd_ws_frame_t frame = {};
	// esp_err_t ret = httpd_ws_recv_frame(req, &frame, 0);

	// printf("Receive: %s\n", esp_err_to_name(ret));

	// if (ret == ESP_OK) {
	// 	printf("Frame type: %d\n", frame.type);
	// 	printf("Frame length: %d\n", (int)frame.len);
	// }

	// return (ESP_OK);



	// httpd_ws_frame_t frame = {};
	// esp_err_t ret = httpd_ws_recv_frame(req, &frame, 0);
	// if (ret != ESP_OK) return (ret);
	// printf("Frame recebido: %d bytes\n\n", (int)frame.len);
	// return (WebServer::send_text_ws(req, "VampetaOS"));



	// httpd_ws_frame_t frame = {};
	// esp_err_t ret = httpd_ws_recv_frame(req, &frame, 0);
	// if (ret != ESP_OK) return (ret);
	// printf("Frame recebido: %d bytes\n", (int)frame.len);
	// if (frame.type != HTTPD_WS_TYPE_TEXT) return (ESP_OK);
	// char *payload = (char *)malloc(frame.len + 1);
	// if (payload == NULL) return (ESP_ERR_NO_MEM);
	// frame.payload = (uint8_t *)payload;
	// ret = httpd_ws_recv_frame(req, &frame, frame.len);
	// if (ret == ESP_OK) {
	// 	payload[frame.len] = '\0';
	// 	printf("Mensagem: %s\n\n", payload);
	// 	ret = WebServer::send_text_ws(req, "VampetaOS\n");
	// }
	// free(payload);
	// return (ret);



	WebSocket_frame frame = WebServer::build_websocket_frame(req);
	// printf("\n========== WS REQUEST ==========\n");
	// printf("Valid: %s\n", (frame.valid) ? "true" : "false");
	// printf("Type: %d\n", frame.type);
	// printf("Length: %zu\n", frame.length);
	// printf("Final: %s\n", (frame.final) ? "true" : "false");
    // printf("Payload: ");
    // if (frame.type == HTTPD_WS_TYPE_TEXT) {
    //     printf("%.*s\n", (int)frame.length, frame.payload.c_str());
	// } else {
    //     printf("[binary data]\n");
	// }
	// printf("==================================\n\n");
	// esp_err_t ret = WebServer::send_text_ws(req, "VampetaOS\n");
	std::string output = WebShell::shell(frame.payload);
	esp_err_t ret = WebServer::send_text_ws(req, output.c_str());
	return (ret);
}