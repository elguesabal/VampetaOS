/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/request_ws.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  build_websocket_frame                                                     |
  |  get_websocket_frame_type                                                  |
  |  get_websocket_frame_payload                                               |
  |  get_websocket_frame_length                                                |
  |  get_websocket_frame_final                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

WebSocket_frame	WebServer::build_websocket_frame(httpd_req_t *req) {
    // WebSocket_frame request = {};

    // if (req == NULL) return (request);

    // httpd_ws_frame_t frame = {};

    // // Obtém as informações do frame e seu tamanho
    // if (httpd_ws_recv_frame(req, &frame, 0) != ESP_OK) return (request);

    // // Verifica o tamanho máximo permitido
    // if (frame.len > MAX_WEBSOCKET_FRAME_SIZE) return (request);

    // // Recebe o payload
    // if (frame.len > 0) {
    //     frame.payload = (uint8_t *)malloc(frame.len);

    //     if (frame.payload == NULL) return (request);

    //     esp_err_t ret = httpd_ws_recv_frame(req, &frame, frame.len);

    //     if (ret != ESP_OK) {
    //         free(frame.payload);
    //         return (request);
    //     }

    //     request.payload.assign(reinterpret_cast<const char *>(frame.payload), frame.len);

    //     free(frame.payload);
    // }

    // request.type = frame.type;
    // request.length = frame.len;
    // request.final = frame.final;
    // request.valid = true;

    // return (request);



	WebSocket_frame frame = {};
	frame.valid = false;
	if (req == NULL) return (frame);
	httpd_ws_frame_t ws_frame = {};
	if (httpd_ws_recv_frame(req, &ws_frame, 0) != ESP_OK) return (frame);
	if (!WebServer::get_websocket_frame_type(&ws_frame, &frame)) return (frame);
	if (!WebServer::get_websocket_frame_payload(req, &ws_frame, &frame)) return (frame);
	if (!WebServer::get_websocket_frame_length(&ws_frame, &frame)) return (frame);
	if (!WebServer::get_websocket_frame_final(&ws_frame, &frame)) return (frame);
	frame.valid = true;
	return (frame);
}

bool	WebServer::get_websocket_frame_type(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame == NULL || frame == NULL) return (false);
	frame->type = ws_frame->type;
	return (true);
}

bool	WebServer::get_websocket_frame_payload(httpd_req_t *req, httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (req == NULL || ws_frame == NULL || frame == NULL) return (false);
	if (ws_frame->len > MAX_WEBSOCKET_FRAME_SIZE) return (false);
	if (ws_frame->len == 0) {
		frame->payload.clear();
		return (true);
	}
	ws_frame->payload = (uint8_t *)malloc(ws_frame->len);
	if (ws_frame->payload == NULL) return (false);
	esp_err_t ret = httpd_ws_recv_frame(req, ws_frame, ws_frame->len);
	if (ret == ESP_OK) frame->payload.assign(reinterpret_cast<const char *>(ws_frame->payload), ws_frame->len);
	free(ws_frame->payload);
	ws_frame->payload = NULL;
	return (ret == ESP_OK);
}

bool	WebServer::get_websocket_frame_length(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame == NULL || frame == NULL) return (false);
	frame->length = ws_frame->len;
	return (true);
}

bool	WebServer::get_websocket_frame_final(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame == NULL || frame == NULL) return (false);
	frame->final = ws_frame->final;
	return (true);
}