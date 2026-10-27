/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /HttpServer/HttpServer.hpp                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "../VampetaOS.hpp"
#include "../Sd/Sd.hpp"
#include "../WebServer/WebServer.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O HTTPSERVER
*/
class HttpServer {
	private:
		uint16_t		port;
		httpd_handle_t	server;

	public:
		// /HttpServer/httpserver.cpp
		static bool	init_httpserver(void);
		HttpServer(uint16_t port);
		~HttpServer(void);
		bool		is_valid(void) const;

		// /HttpServer/route.cpp
		bool		add_get(const char *path, esp_err_t (*handler)(httpd_req_t *));
		bool		remove_get(const char *path);
		bool		add_post(const char *path, esp_err_t (*handler)(httpd_req_t *));
		bool		remove_post(const char *path);

	private:
		// /WebServer/directory.cpp
		static bool	check_dir(void);
};

#endif