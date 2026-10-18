/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebTerminal/register.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  register_index_html                                                       |
  |  register_style_css                                                        |
  |  register_print_js                                                         |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

/**
 * @author elguesabal
 * @brief REGISTRA A ROTA / COM A RESPOSTA DO ARQUIVO /index.html
 * @return RETORNA true EM CASO DE ROTA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO register_route FALHE
*/
bool WebTerminal::register_index_html(void) {
	if (!WebServer::register_route(PORT, "/", WebTerminal::index_html)) {
		WebServer::close_port(PORT);
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief REGISTRA A ROTA /css/style.css COM A RESPOSTA DO ARQUIVO /css/style.css
 * @return RETORNA true EM CASO DE ROTA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO register_route FALHE
*/
bool WebTerminal::register_style_css(void) {
	if (!WebServer::register_route(PORT, "/css/style.css", WebTerminal::style_css)) {
		WebServer::close_port(PORT);
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief REGISTRA A ROTA /js/print.js COM A RESPOSTA DO ARQUIVO /js/print.js
 * @return RETORNA true EM CASO DE ROTA REGISTRADA COM SUCESSO
 * @return RETORNA false CASO register_route FALHE
*/
bool WebTerminal::register_print_js(void) {
	if (!WebServer::register_route(PORT, "/js/print.js", WebTerminal::print_js)) {
		WebServer::close_port(PORT);
		return (false);
	}
	return (true);
}



bool WebTerminal::register_test(void) {
	if (!WebServer::register_route(PORT, "/test", WebTerminal::test)) {
		WebServer::close_port(PORT);
		return (false);
	}
	return (true);
}

// DEVO ADICIONAR close_port A register_route PARA EVITAR ESSES METODOS ACIMA?