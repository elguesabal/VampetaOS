/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/webserver.cpp                                                  |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  test_html                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief PREPARA A PAGINA HTML PARA SER ENVIADA
 * @return RETORNA ESP_OK EM CASO DE SUCESSO 
*/
esp_err_t	WebServer::test_html(httpd_req_t *req) {
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