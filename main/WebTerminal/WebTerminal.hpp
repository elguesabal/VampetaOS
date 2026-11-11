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
#include "../Shell/Shell.hpp"

#define PORT 80

/**
 * @author elguesabal
 * @brief STRUCT USADO PARA ARMAZENAR QUAIS CONEXOES FD ESTAO ASSOCIADOS A QUAIS SHELLS
*/
struct WebTerminal_session {
	int		fd;
	Shell	*shell;
};

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WEBTERMINAL
*/
class WebTerminal {
	private:
		static HttpServer	*server;
		static std::map<int, WebTerminal_session> sessions;

	public:
		// /WebTerminal/webterminal.cpp
		static bool			init_webterminal(void);

	private:
		// /WebTerminal/webterminal.cpp
		static bool			init_server(void);
		static bool			init_handler_disconnect_ws(void);
		static bool			init_routes(void);

		// /WebTerminal/routes.cpp
		static esp_err_t	index_html(httpd_req_t *req);
		static esp_err_t	style_css(httpd_req_t *req);
		static esp_err_t	variables_js(httpd_req_t *req);
		static esp_err_t	connection_js(httpd_req_t *req);
		static esp_err_t	events_js(httpd_req_t *req);
		static esp_err_t	keys_js(httpd_req_t *req);
		static esp_err_t	print_js(httpd_req_t *req);
		static esp_err_t	connect_ws(httpd_req_t *req);
		static esp_err_t	input_shell(httpd_req_t *req);
		static void			disconnect_ws(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
};

#endif