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

/**
 * @author elguesabal
 * @brief METODO QUE INTERPRETA UM FRAME WS E SALVA E RETORNA UM STRUCT WebSocket_frame
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DO FRAME WS RECEBIDA PELO SERVIDOR
 * @return RETORNA UM WebSocket_frame COMPLETO EM CASO DO FRAME FOR VALIDO
 * @return RETORNA UM WebSocket_frame VAZIO CASO req SEJA NULL
 * @return RETORNA UM WebSocket_frame VAZIO CASO httpd_ws_recv_frame FALHE
 * @return RETORNA UM WebSocket_frame INCOMPLETO CASO WebSocket_frame FALHE
 * @return RETORNA UM WebSocket_frame INCOMPLETO CASO get_websocket_frame_payload FALHE
 * @return RETORNA UM WebSocket_frame INCOMPLETO CASO get_websocket_frame_length FALHE
 * @return RETORNA UM WebSocket_frame INCOMPLETO CASO get_websocket_frame_final FALHE
*/
WebSocket_frame	WebServer::build_websocket_frame(httpd_req_t *req) {
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

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TIPO DO FRAME
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
 * @return RETORNA true CASO O METODO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO ws_frame SEJA NULL
 * @return RETORNA false CASO frame SEJA NULL
*/
bool	WebServer::get_websocket_frame_type(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame == NULL || frame == NULL) return (false);
	frame->type = ws_frame->type;
	return (true);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O PAYLOAD DO FRAME
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DO FRAME WS RECEBIDA PELO SERVIDOR
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
 * @return RETORNA true CASO O METODO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO ws_frame SEJA NULL
 * @return RETORNA false CASO frame SEJA NULL
 * @return RETORNA false CASO O TAMANHO DO PAYLOAD ULTRAPASSE MAX_REQUEST_BODY_SIZE
 * @return RETORNA false CASO O TAMANHO DO PAYLOAD SEJA 0
 * @return RETORNA false CASO ws_frame->payload SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @return RETORNA false CASO httpd_ws_recv_frame FALHE
*/
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

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TAMANHO DO FRAME
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
 * @return RETORNA true CASO O METODO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO ws_frame SEJA NULL
 * @return RETORNA false CASO frame SEJA NULL
*/
bool	WebServer::get_websocket_frame_length(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame == NULL || frame == NULL) return (false);
	frame->length = ws_frame->len;
	return (true);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA SE JA CHEGOU NO FINAL DO FRAME
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
 * @return RETORNA true CASO O METODO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO ws_frame SEJA NULL
 * @return RETORNA false CASO frame SEJA NULL
*/
bool	WebServer::get_websocket_frame_final(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame == NULL || frame == NULL) return (false);
	frame->final = ws_frame->final;
	return (true);
}