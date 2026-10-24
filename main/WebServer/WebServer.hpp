VampetaOs/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
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

		// /WebServer/port.cpp
		static bool				open_port(uint16_t port);
		static bool				close_port(uint16_t port);

		// /WebServer/route.cpp
		static bool				register_route(uint16_t port, httpd_method_t method, const char *url, esp_err_t (*handler)(httpd_req_t *));
		static bool				unregister_route(uint16_t port, httpd_method_t method, const char *url);
		static bool				register_get(uint16_t port, const char *url, esp_err_t (*handler)(httpd_req_t *));
		static bool				unregister_get(uint16_t port, const char *url);

		// /WebServer/response.cpp
		static esp_err_t		send_file_flash(httpd_req_t *req, const char *content_type, const uint8_t *start, const uint8_t *end);
		static esp_err_t		send_text(httpd_req_t *req, const char *text);

	private:
		// /WebServer/directory.cpp
		static bool				check_dir(void);
};

#endif