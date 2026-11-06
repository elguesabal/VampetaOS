/*
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

#define MAX_REQUEST_BODY_SIZE 4096

/**
 * @author elguesabal
 * @brief STRUCT USADO PARA ARMAZENAR OS DADOS INTERPRETADOS DE UMA REQUISICAO HTTP REBIDA
*/
struct Resquest_http {
	bool			valid;
    httpd_method_t	method;
    std::string		path;
    std::string		query;
    std::string		body;
    std::string		content_type;
    size_t			content_length;
	// headers
	// client_ip
	// cookies
	// authorization
};

/**
 * @author elguesabal
 * @brief STRUCT USADO PARA ARMAZENAR OS DADOS INTERPRETADOS DE UMA REQUISICAO WS REBIDA
*/
struct Resquest_ws {

};

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
		static httpd_handle_t	get_server(uint16_t port);

		// /WebServer/route.cpp
		static bool				register_route_http(uint16_t port, httpd_method_t method, const char *url, esp_err_t (*handler)(httpd_req_t *));
		static bool				register_route_websocket(uint16_t port, const char *url, esp_err_t (*handler)(httpd_req_t *));
		static bool				unregister_route(uint16_t port, httpd_method_t method, const char *url);

		// /WebServer/request_http.cpp
		static Resquest_http	build_request_http(httpd_req_t *req);

		// /WebServer/request_ws.cpp
		// static Resquest_http	build_request_ws(httpd_req_t *req);

		// /WebServer/response_http.cpp
		static const char		*status_http(const uint16_t code);
		static esp_err_t		send_status_http(httpd_req_t *req, const uint16_t status);
		static esp_err_t		send_file_flash_http(httpd_req_t *req, const uint16_t status, const char *content_type, const uint8_t *start, const uint8_t *end);
		static esp_err_t		send_text_http(httpd_req_t *req, const uint16_t status, const char *text);
		static esp_err_t		send_json_http(httpd_req_t *req, const uint16_t status, const char *json);

		// /WebServer/response_ws.cpp
		static esp_err_t		send_text_ws(httpd_req_t *req, const char *text);

	private:
		// /WebServer/directory.cpp
		static bool				check_dir(void);

		// /WebServer/route.cpp
		static bool				register_route(uint16_t port, httpd_method_t method, const char *url, esp_err_t (*handler)(httpd_req_t *), bool websocket);
};

#endif