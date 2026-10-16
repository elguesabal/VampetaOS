/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/WebServer.hpp                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "../VampetaOS.hpp"
#include "../Sd/Sd.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WEBSERVER
*/
class WebServer {
	private:
		// /WebServer/webserver.cpp
		static std::map<uint16_t, httpd_handle_t>	servers;

	public:
		// /WebServer/webserver.cpp
		static bool				init_webserver(void);
		static bool				open_port(uint16_t port);
		static bool				close_port(uint16_t port);
		static bool				register_routes(uint16_t port, const char *url);

		// /WebServer/directory.cpp
		static bool				check_dir(void);

		// /WebServer/terminal.cpp
		static esp_err_t		test_html(httpd_req_t *req);
};

#endif