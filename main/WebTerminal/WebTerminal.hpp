/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebTerminal/WebTerminal.hpp                                              |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef WEBTERMINAL_H
#define WEBTERMINAL_H

#include "../VampetaOS.hpp"
#include "../WebServer/WebServer.hpp"

#define PORT 80

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WEBTERMINAL
*/
class WebTerminal {
	public:
		// /WebTerminal/webterminal.cpp
		static bool			init_webterminal(void);

		// /WebTerminal/register.cpp
		static bool			register_index_html(void);
		static bool			register_style_css(void);
		static bool			register_print_js(void);
static bool			register_test(void);

		// /WebTerminal/files.cpp
		static esp_err_t	index_html(httpd_req_t *req);
		static esp_err_t	style_css(httpd_req_t *req);
		static esp_err_t	print_js(httpd_req_t *req);
static esp_err_t	test(httpd_req_t *req);
};

#endif