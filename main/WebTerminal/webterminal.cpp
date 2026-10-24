/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebTerminal/webterminal.cpp                                              |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_webterminal                                                          |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebTerminal.hpp"

/**
 * @author elguesabal
 * @brief ABRE UMA PORTA E REGISTRA AS ROTAS NECESSARIAS PARA INICIAR O WEBTERMINAL
 * @return RETORNA true EM CASO DO WEBTERMINAL INICIADO COM SUCESSO
 * @return RETORNA false CASO open_port FALHE
 * @return RETORNA false CASO register_index_html FALHE
 * @return RETORNA false CASO register_style_css FALHE
 * @return RETORNA false CASO register_print_js FALHE
*/
bool	WebTerminal::init_webterminal(void) {
	if (!WebServer::open_port(PORT)) return (false);
	if (!WebServer::register_get(PORT, "/", WebTerminal::index_html)) return (false);
	if (!WebServer::register_get(PORT, "/css/style.css", WebTerminal::style_css)) return (false);
	if (!WebServer::register_get(PORT, "/js/print.js", WebTerminal::print_js)) return (false);
	printf("WebTerminal: OK\n");
	return (true);
}