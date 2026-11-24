/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
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
#include "Shell/Shell.hpp"

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

esp_err_t	test(httpd_req_t *req) {
	WebSocket_frame frame = WebServer::build_websocket_frame(req);
	if (frame.error != ESP_OK) return (frame.error);
	printf("%s\n", frame.payload.c_str());
	return (WebServer::send_text_ws(req, "VampetaOS"));
}

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
	if (!Shell::init_shell()) return;
	test();
	printf("VampetaOS\n");
}

























// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"

// #include "esp_system.h"
// #include "esp_log.h"
// #include "esp_err.h"
// #include "nvs_flash.h"

// #include "esp_event.h"
// #include "esp_netif.h"
// #include "esp_wifi.h"

// #include "esp_http_server.h"

// // ============================================================
// // CONFIGURATION
// // ============================================================

// #define WIFI_SSID       "ELGUESABAL"
// #define WIFI_PASSWORD   "12345678"

// #define SERVER_PORT     80
// #define MAX_WS_PAYLOAD  1024

// static const char *TAG = "WS_TEST";

// // ============================================================
// // WIFI
// // ============================================================

// static EventGroupHandle_t wifi_events;

// static const int WIFI_CONNECTED_BIT = BIT0;
// static const int WIFI_FAIL_BIT      = BIT1;

// static int retry_count = 0;
// static const int MAX_RETRIES = 5;

// static void wifi_event_handler(
//     void *arg,
//     esp_event_base_t event_base,
//     int32_t event_id,
//     void *event_data
// ) {
//     if (event_base == WIFI_EVENT &&
//         event_id == WIFI_EVENT_STA_START) {

//         esp_wifi_connect();
//     }

//     else if (event_base == WIFI_EVENT &&
//              event_id == WIFI_EVENT_STA_DISCONNECTED) {

//         if (retry_count < MAX_RETRIES) {
//             retry_count++;

//             ESP_LOGW(TAG, "WiFi disconnected. Retry %d",
//                      retry_count);

//             esp_wifi_connect();
//         }
//         else {
//             xEventGroupSetBits(wifi_events, WIFI_FAIL_BIT);
//         }
//     }

//     else if (event_base == IP_EVENT &&
//              event_id == IP_EVENT_STA_GOT_IP) {

//         ip_event_got_ip_t *event =
//             (ip_event_got_ip_t *)event_data;

//         ESP_LOGI(TAG, "================================");
//         ESP_LOGI(TAG, "WIFI CONNECTED");
//         ESP_LOGI(TAG, "IP: " IPSTR, IP2STR(&event->ip_info.ip));
//         ESP_LOGI(TAG, "================================");

//         retry_count = 0;

//         xEventGroupSetBits(wifi_events, WIFI_CONNECTED_BIT);
//     }
// }

// static void wifi_init(void) {

//     wifi_events = xEventGroupCreate();

//     ESP_ERROR_CHECK(esp_netif_init());

//     ESP_ERROR_CHECK(esp_event_loop_create_default());

//     esp_netif_create_default_wifi_sta();

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));

//     ESP_ERROR_CHECK(
//         esp_event_handler_register(
//             WIFI_EVENT,
//             ESP_EVENT_ANY_ID,
//             &wifi_event_handler,
//             NULL
//         )
//     );

//     ESP_ERROR_CHECK(
//         esp_event_handler_register(
//             IP_EVENT,
//             IP_EVENT_STA_GOT_IP,
//             &wifi_event_handler,
//             NULL
//         )
//     );

//     wifi_config_t wifi_config = {};

//     snprintf(
//         (char *)wifi_config.sta.ssid,
//         sizeof(wifi_config.sta.ssid),
//         "%s",
//         WIFI_SSID
//     );

//     snprintf(
//         (char *)wifi_config.sta.password,
//         sizeof(wifi_config.sta.password),
//         "%s",
//         WIFI_PASSWORD
//     );

//     ESP_ERROR_CHECK(
//         esp_wifi_set_mode(WIFI_MODE_STA)
//     );

//     ESP_ERROR_CHECK(
//         esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
//     );

//     ESP_ERROR_CHECK(
//         esp_wifi_start()
//     );

//     ESP_LOGI(TAG, "Waiting for WiFi...");

//     EventBits_t bits = xEventGroupWaitBits(
//         wifi_events,
//         WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
//         pdFALSE,
//         pdFALSE,
//         portMAX_DELAY
//     );

//     if (bits & WIFI_FAIL_BIT) {
//         ESP_LOGE(TAG, "Could not connect to WiFi");
//         ESP_ERROR_CHECK(ESP_FAIL);
//     }
// }

// // ============================================================
// // HTML
// // ============================================================

// static const char *HTML_PAGE = R"HTML(
// <!DOCTYPE html>
// <html lang="pt-BR">

// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1">

//     <title>WebSocket Test</title>

//     <style>
//         body {
//             background: #111;
//             color: white;
//             font-family: monospace;
//             padding: 30px;
//         }

//         #output {
//             background: #222;
//             padding: 15px;
//             min-height: 200px;
//             white-space: pre-wrap;
//             overflow-wrap: anywhere;
//         }

//         input {
//             padding: 10px;
//             margin-top: 15px;
//             width: 70%;
//         }

//         button {
//             padding: 10px;
//         }
//     </style>
// </head>

// <body>

//     <h1 id="title">WebSocket Test</h1>

//     <p id="status">Connecting...</p>

//     <div id="output"></div>

//     <input id="message" placeholder="Digite uma mensagem">

//     <button onclick="sendMessage()">Enviar</button>

//     <script>

//         const output = document.getElementById("output");
//         const status = document.getElementById("status");

//         function print(text) {
//             output.textContent += text + "\n";
//         }

//         const page = location.pathname === "/page2"
//             ? "PAGE 2"
//             : "PAGE 1";

//         document.getElementById("title").textContent = page;

//         const ws = new WebSocket(
//             "ws://" + location.host + "/ws"
//         );

//         ws.onopen = () => {
//             status.textContent = "CONNECTED";
//             print("[CLIENT] WebSocket connected");
//             ws.send("Hello from " + page);
//         };

//         ws.onmessage = (event) => {
//             print("[SERVER] " + event.data);
//         };

//         ws.onerror = () => {
//             status.textContent = "ERROR";
//             print("[CLIENT] WebSocket error");
//         };

//         ws.onclose = () => {
//             status.textContent = "DISCONNECTED";
//             print("[CLIENT] WebSocket closed");
//         };

//         function sendMessage() {
//             const input = document.getElementById("message");

//             if (ws.readyState !== WebSocket.OPEN) {
//                 print("[CLIENT] WebSocket is not connected");
//                 return;
//             }

//             ws.send(input.value);

//             print("[CLIENT] " + input.value);

//             input.value = "";
//         }

//         document.getElementById("message")
//             .addEventListener("keydown", (event) => {
//                 if (event.key === "Enter") {
//                     sendMessage();
//                 }
//             });

//     </script>

// </body>
// </html>
// )HTML";

// // ============================================================
// // HTTP HANDLER
// // ============================================================

// static esp_err_t page_handler(httpd_req_t *req) {

//     ESP_LOGI(TAG, "HTTP REQUEST: %s", req->uri);

//     httpd_resp_set_type(req, "text/html");

//     return httpd_resp_send(
//         req,
//         HTML_PAGE,
//         HTTPD_RESP_USE_STRLEN
//     );
// }

// // ============================================================
// // WEBSOCKET HANDLER
// // ============================================================

// static esp_err_t websocket_handler(httpd_req_t *req) {

//     // --------------------------------------------------------
//     // HANDSHAKE
//     // --------------------------------------------------------

//     if (req->method == HTTP_GET) {

//         int fd = httpd_req_to_sockfd(req);

//         ESP_LOGI(TAG, "================================");
//         ESP_LOGI(TAG, "[WS] CONNECT START");
//         ESP_LOGI(TAG, "[WS] FD: %d", fd);
//         ESP_LOGI(TAG, "[WS] HANDSHAKE SUCCESS");
//         ESP_LOGI(TAG, "================================");

//         return ESP_OK;
//     }

//     // --------------------------------------------------------
//     // RECEIVE FRAME HEADER
//     // --------------------------------------------------------

//     httpd_ws_frame_t frame = {};

//     esp_err_t err = httpd_ws_recv_frame(
//         req,
//         &frame,
//         0
//     );

//     if (err != ESP_OK) {
//         ESP_LOGE(TAG, "[WS] FRAME HEADER ERROR: %s",
//                  esp_err_to_name(err));

//         return err;
//     }

//     if (frame.len > MAX_WS_PAYLOAD) {
//         ESP_LOGW(TAG, "[WS] Payload too large: %u",
//                  (unsigned int)frame.len);

//         return ESP_ERR_INVALID_SIZE;
//     }

//     // --------------------------------------------------------
//     // RECEIVE FRAME PAYLOAD
//     // --------------------------------------------------------

//     frame.payload = (uint8_t *)malloc(frame.len + 1);

//     if (frame.payload == NULL) {
//         return ESP_ERR_NO_MEM;
//     }

//     err = httpd_ws_recv_frame(
//         req,
//         &frame,
//         frame.len
//     );

//     if (err != ESP_OK) {
//         free(frame.payload);

//         ESP_LOGE(TAG, "[WS] FRAME RECEIVE ERROR");

//         return err;
//     }

//     frame.payload[frame.len] = '\0';

//     int fd = httpd_req_to_sockfd(req);

//     ESP_LOGI(
//         TAG,
//         "[WS] FD: %d | RECEIVED %u BYTES",
//         fd,
//         (unsigned int)frame.len
//     );

//     // --------------------------------------------------------
//     // HANDLE FRAME TYPES
//     // --------------------------------------------------------

//     if (frame.type == HTTPD_WS_TYPE_TEXT) {

//         ESP_LOGI(
//             TAG,
//             "[WS] MESSAGE: %.*s",
//             (int)frame.len,
//             (char *)frame.payload
//         );

//         // Echo: return the same message to its sender.
//         err = httpd_ws_send_frame(req, &frame);
//     }

//     else if (frame.type == HTTPD_WS_TYPE_BINARY) {

//         err = httpd_ws_send_frame(req, &frame);
//     }

//     else if (frame.type == HTTPD_WS_TYPE_PING) {

//         frame.type = HTTPD_WS_TYPE_PONG;

//         err = httpd_ws_send_frame(req, &frame);
//     }

//     else if (frame.type == HTTPD_WS_TYPE_CLOSE) {

//         ESP_LOGI(TAG, "[WS] CLIENT REQUESTED CLOSE");

//         err = ESP_OK;
//     }

//     else {

//         ESP_LOGW(TAG, "[WS] UNKNOWN FRAME TYPE: %d",
//                  (int)frame.type);

//         err = ESP_OK;
//     }

//     free(frame.payload);

//     if (err != ESP_OK) {
//         ESP_LOGE(TAG, "[WS] SEND ERROR: %s",
//                  esp_err_to_name(err));
//     }

//     return err;
// }

// // ============================================================
// // HTTP SERVER
// // ============================================================

// static httpd_handle_t server = NULL;

// static void http_server_init(void) {

//     httpd_config_t config = HTTPD_DEFAULT_CONFIG();

//     config.server_port = SERVER_PORT;

//     // Allow multiple simultaneous client connections.
//     config.max_open_sockets = 7;

//     // Do not purge connections automatically.
//     config.lru_purge_enable = false;

//     ESP_LOGI(TAG, "Starting HTTP server...");

//     ESP_ERROR_CHECK(
//         httpd_start(&server, &config)
//     );

//     // --------------------------------------------------------
//     // PAGE 1
//     // --------------------------------------------------------

//     httpd_uri_t page1 = {};

//     page1.uri = "/";
//     page1.method = HTTP_GET;
//     page1.handler = page_handler;
//     page1.user_ctx = NULL;

//     ESP_ERROR_CHECK(
//         httpd_register_uri_handler(server, &page1)
//     );

//     // --------------------------------------------------------
//     // PAGE 2
//     // --------------------------------------------------------

//     httpd_uri_t page2 = {};

//     page2.uri = "/page2";
//     page2.method = HTTP_GET;
//     page2.handler = page_handler;
//     page2.user_ctx = NULL;

//     ESP_ERROR_CHECK(
//         httpd_register_uri_handler(server, &page2)
//     );

//     // --------------------------------------------------------
//     // WEBSOCKET
//     // --------------------------------------------------------

//     httpd_uri_t websocket = {};

//     websocket.uri = "/ws";
//     websocket.method = HTTP_GET;
//     websocket.handler = websocket_handler;
//     websocket.user_ctx = NULL;
//     websocket.is_websocket = true;

//     ESP_ERROR_CHECK(
//         httpd_register_uri_handler(server, &websocket)
//     );

//     ESP_LOGI(TAG, "================================");
//     ESP_LOGI(TAG, "HTTP SERVER STARTED");
//     ESP_LOGI(TAG, "PORT: %d", SERVER_PORT);
//     ESP_LOGI(TAG, "MAX OPEN SOCKETS: %d",
//              config.max_open_sockets);
//     ESP_LOGI(TAG, "================================");
// }

// // ============================================================
// // APP MAIN
// // ============================================================

// extern "C" void app_main(void) {

//     esp_err_t ret = nvs_flash_init();

//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
//         ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

//         ESP_ERROR_CHECK(nvs_flash_erase());

//         ret = nvs_flash_init();
//     }

//     ESP_ERROR_CHECK(ret);

//     ESP_LOGI(TAG, "Initializing WiFi...");

//     wifi_init();

//     http_server_init();

//     ESP_LOGI(TAG, "================================");
//     ESP_LOGI(TAG, "SERVER READY");
//     ESP_LOGI(TAG, "================================");

//     while (true) {
//         vTaskDelay(pdMS_TO_TICKS(10000));
//     }
// }
