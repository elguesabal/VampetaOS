/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /main.c                                                                   |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  test                                                                      |
  |  app_main                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "VampetaOS.hpp"

#include "Sd/Sd.hpp"
#include "System/System.hpp"
#include "Wifi/Wifi.hpp"
#include "WebServer/WebServer.hpp"
#include "HttpServer/HttpServer.hpp"
#include "WebTerminal/WebTerminal.hpp"

// #include "esp_heap_caps.h"

/**
 * @author elguesabal
 * @brief FUNCAO DE TESTES
*/
void	test(void) {
// printf("RAM livre: %u KB\n\n\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024);

// if (!Sd::create_dir("/directory")) printf("reate_dir -> %s\n\n\n", strerror(errno));

// if (!Sd::remove_dir("/directory")) printf("remove_dir -> %s\n\n\n", strerror(errno));

// if (Sd::exist_dir("/directory")) printf("existe este diretorio\n\n\n");

// if (!Sd::create_file("/file")) printf("create_file -> %s\n\n\n", strerror(errno));

// if (!Sd::create_file("/file.txt", "VampetaOS")) printf("create_file -> %s\n\n\n", strerror(errno));

// if (!Sd::write_file("/file.txt", "VampetaOS")) printf("write_file -> %s\n\n\n", strerror(errno));

// if (!Sd::set_config("/Wifi/WIFI_CONFIG", "WIFI", "VampetaOS")) printf("set_config -> %s\n\n\n", strerror(errno));

// std::string wifi = Sd::get_config("/Wifi/WIFI_CONFIG", "WIFI");
// if (!wifi.empty()) {
// 	printf("%s\n", wifi.c_str());
// } else if (errno) {
// 	printf("get_config -> %s\n\n\n", strerror(errno));
// } else if (errno == 0) {
// 	printf("errno == 0");
// }
// printf("\n\n\n");

// std::vector<Sd::DirectoryEntry>	ls = Sd::list_dir("/");
// if (errno != 0) {
// 	printf("list_dir -> %s\n\n\n", strerror(errno));
// } else if (!ls.empty()) {
// 	for (const Sd::DirectoryEntry& entry : ls) printf("%s\n\n\n", entry.name.c_str());
// 	printf("\n\n\n");
// }

// if (!Sd::delete_dir("/test")) printf("delete_dir -> %s\n\n\n", strerror(errno));

// std::string wifi_config;
// if (!Sd::read_file("/Wifi/WIFI_CONFIG", wifi_config)) printf("read_file -> %s\n\n\n", strerror(errno));
// printf("%s\n\n\n", wifi_config.c_str());
// printf("\n\n\n");

// printf("SSID -> \"%s\"\n", Wifi::get_ssid().c_str());
// printf("PASSWORD -> \"%s\"\n", Wifi::get_password().c_str());
// printf("\n\n\n");
}

// esp_err_t	response(httpd_req_t *req) {
// 	// return (WebServer::send_text(req, 200, "VampetaOS"));
// 	return (WebServer::send_json(req, 200, "{\"os\":\"VampetaOS\",\"status\":\"running\"}"));
// }

/**
 * @author elguesabal
 * @brief FUNCAO PRINCIPAL
*/
extern "C" void	app_main(void) {
	if (!Sd::init_sd()) return;
	if (!System::init_system()) return;
	if (!Wifi::init_wifi()) return;
	if (!WebServer::init_webserver()) return;
	if (!HttpServer::init_httpserver()) return;
	if (!WebTerminal::init_webterminal()) return;

	test();

// static HttpServer server(4242);
// server.add_get("/vampeta", response);

	printf("VampetaOS\n");
}