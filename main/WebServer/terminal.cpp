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
	extern const uint8_t terminal_html_start[] asm("_binary_index_html_start");
	extern const uint8_t terminal_html_end[] asm("_binary_index_html_end");
	httpd_resp_set_type(req, "text/html; charset=UTF-8");
	return (httpd_resp_send(req, reinterpret_cast<const char *>(terminal_html_start), terminal_html_end - terminal_html_start));
}

// PAREI AKI TENTANDO ENTENDER COMO ENVIAR O CSS E JS EM OUTRAS ROTAS