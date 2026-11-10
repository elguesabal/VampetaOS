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
#define MAX_WEBSOCKET_FRAME_SIZE 1024

/**
 * @author elguesabal
 * @brief STRUCT USADO PARA ARMAZENAR OS DADOS INTERPRETADOS DE UMA REQUISICAO HTTP REBIDA
*/
struct Resquest_http {
	esp_err_t		error;
    httpd_method_t	method;
    std::string		path;
    std::string		query;
    std::string		content_type;
    size_t			content_length;
    std::string		body;
	// headers
	// client_ip
	// cookies
	// authorization
};

/**
 * @author elguesabal
 * @brief STRUCT USADO PARA ARMAZENAR OS DADOS INTERPRETADOS DE UMA REQUISICAO DE CONEXAO WS REBIDA
*/
struct WebSocket_connect {
	esp_err_t	error;
	int			fd;
};

/**
 * @author elguesabal
 * @brief STRUCT USADO PARA ARMAZENAR OS DADOS INTERPRETADOS DE UM FRAME WEBSOCKET
*/
struct WebSocket_frame {
	esp_err_t		error;
	httpd_ws_type_t	type;
	size_t			length;
	bool			final;
	std::string		payload;
};

// /**
//  * @author elguesabal
//  * @brief STRUCT USADO PARA ARMAZENAR OS DADOS INTERPRETADOS DE UM WEBSOCKET DESCONECTADO
// */
// struct WebSocket_disconnect {
// 	int		fd;
// 	bool	valid;
// };

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
		static bool					init_webserver(void);

		// /WebServer/port.cpp
		static bool					open_port(uint16_t port);
		static bool					close_port(uint16_t port);
		static httpd_handle_t		get_server(uint16_t port);

		// /WebServer/route.cpp
		static bool					register_route_http(uint16_t port, httpd_method_t method, const char *url, esp_err_t (*handler)(httpd_req_t *));
		static bool					register_route_websocket(uint16_t port, const char *url, esp_err_t (*handler)(httpd_req_t *), esp_err_t (*connect)(httpd_req_t *));
		static bool					unregister_route(uint16_t port, httpd_method_t method, const char *url);

		// /WebServer/request_http.cpp
		static Resquest_http		build_request_http(httpd_req_t *req);

		// /WebServer/request_ws.cpp
		static WebSocket_connect	build_websocket_connect(httpd_req_t *req);
		static WebSocket_frame		build_websocket_frame(httpd_req_t *req);

		// /WebServer/response_http.cpp
		static const char			*status_http(const uint16_t code);
		static esp_err_t			send_status_http(httpd_req_t *req, const uint16_t status);
		static esp_err_t			send_file_flash_http(httpd_req_t *req, const uint16_t status, const char *content_type, const uint8_t *start, const uint8_t *end);
		static esp_err_t			send_text_http(httpd_req_t *req, const uint16_t status, const char *text);
		static esp_err_t			send_json_http(httpd_req_t *req, const uint16_t status, const char *json);

		// /WebServer/response_ws.cpp
		static esp_err_t			send_text_ws(httpd_req_t *req, const char *text);

	private:
		// /WebServer/directory.cpp
		static bool					check_dir(void);

		// /WebServer/route.cpp
		static bool					register_route(uint16_t port, httpd_method_t method, const char *url, esp_err_t (*handler)(httpd_req_t *), bool websocket, esp_err_t (*ws_connect)(httpd_req_t *));

		// /WebServer/request_http.cpp
		static void					get_request_method(httpd_req_t *req, Resquest_http *request);
		static void					get_request_path(httpd_req_t *req, Resquest_http *request);
		static void					get_request_query(httpd_req_t *req, Resquest_http *request);
		static void					get_request_body(httpd_req_t *req, Resquest_http *request);
		static void					get_request_content_type(httpd_req_t *req, Resquest_http *request);
		static void					get_request_content_length(httpd_req_t *req, Resquest_http *request);

		// /WebServer/request_ws.cpp
		static void					get_websocket_connect_fd(httpd_req_t *req, WebSocket_connect *connect);
		static void					get_websocket_frame_type(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame);
		static void					get_websocket_frame_length(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame);
		static void					get_websocket_frame_final(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame);
		static void					get_websocket_frame_payload(httpd_req_t *req, httpd_ws_frame_t *ws_frame, WebSocket_frame *frame);

		// /WebServer/response_error.cpp
		static bool					register_response_error(httpd_handle_t server);
		static esp_err_t			not_found(httpd_req_t *req, httpd_err_code_t error);
		static esp_err_t			internal_server_error(httpd_req_t *req, httpd_err_code_t error);
};

#endif