/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/webserver.cpp                                                  |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |                                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

httpd_handle_t WebServer::server = NULL;

esp_err_t	test_html(httpd_req_t *req) {
	const char *html =
		"<!DOCTYPE html>"
		"<html lang=\"pt-BR\">"
		"<head>"
			"<meta charset=\"UTF-8\">"
			"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
			"<title>VampetaOS</title>"
		"</head>"
		"<body>"
			"<h1>VampetaOS</h1>"
			"<p>Servidor HTTP funcionando!</p>"
		"</body>"
		"</html>";
	httpd_resp_set_type(req, "text/html; charset=UTF-8");
	return (httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN));
}

bool	WebServer::init_webserver(void) {
	if (!WebServer::check_dir()) return (false);
	if (!WebServer::init()) return (false);
	printf("WebServer: OK\n");
	return (true);
}

bool	WebServer::init(void) {
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	httpd_handle_t server = NULL;
	esp_err_t ret = httpd_start(&server, &config);
	if (ret != ESP_OK) {
		printf("httpd_start: %s\n", esp_err_to_name(ret));
		return (false);
	}

	httpd_uri_t uri = {};
	uri.uri = "/";
	uri.method = HTTP_GET;
	uri.handler = test_html;
	uri.user_ctx = NULL;

	ret = httpd_register_uri_handler(server, &uri);
	if (ret != ESP_OK) {
		printf("httpd_register_uri_handler: %s\n", esp_err_to_name(ret));
		httpd_stop(server);
		return (false);
	}

	WebServer::server = server;
	return (true);
}

// DIVIDIR O METODO init PARA CRIAR UM METODO Q CRIE ROTAS