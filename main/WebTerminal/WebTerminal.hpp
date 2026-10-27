/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
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
#include "../HttpServer/HttpServer.hpp"

#define PORT 80

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WEBTERMINAL
*/
class WebTerminal {
	private:
		static HttpServer	*server;

	public:
		// /WebTerminal/webterminal.cpp
		static bool			init_webterminal(void);

	private:
		// /WebTerminal/webterminal.cpp
		static bool			init_server(void);
		static bool			init_routes(void);

		// /WebTerminal/routes.cpp
		static esp_err_t	index_html(httpd_req_t *req);
		static esp_err_t	style_css(httpd_req_t *req);
		static esp_err_t	print_js(httpd_req_t *req);
};

#endif