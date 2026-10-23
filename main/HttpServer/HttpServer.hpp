/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
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

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O HTTPSERVER
*/
class HttpServer {
	private:
		uint16_t		port;
		httpd_handle_t	server;

		// /HttpServer/HttpServer.cpp
		static std::map<uint16_t, httpd_handle_t>	servers;

	public:
		// /HttpServer/HttpServer.cpp
		static bool				init_httpserver(void);
		HttpServer(uint16_t port);
		~HttpServer();

	private:
		// /WebServer/directory.cpp
		static bool				check_dir(void);
};

#endif