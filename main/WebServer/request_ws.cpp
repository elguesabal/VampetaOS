/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/request_ws.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  build_websocket_connect                                                   |
  |  get_websocket_connect_fd                                                  |
  |  build_websocket_frame                                                     |
  |  get_websocket_frame_type                                                  |
  |  get_websocket_frame_length                                                |
  |  get_websocket_frame_final                                                 |
  |  get_websocket_frame_payload                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE INTERPRETA INFORMACOES DE CONEXAO DO WS E SALVA E RETORNA UM STRUCT WebSocket_frame
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DE CONEXAO WS RECEBIDA PELO SERVIDOR
 * @return RETORNA UM WebSocket_disconnect COMPLETO EM CASO DA CONEXAO FOR VALIDA
 * @return RETORNA UM WebSocket_disconnect VAZIO CASO req SEJA NULL
 * @return RETORNA UM WebSocket_disconnect VAZIO CASO get_websocket_connect_fd FALHE
*/
WebSocket_connect	WebServer::build_websocket_connect(httpd_req_t *req) {
	WebSocket_connect connect = {};
	if (req == NULL) {
		connect.error = ESP_ERR_INVALID_ARG;
		return (connect);
	}
	connect.error = ESP_OK;
	WebServer::get_websocket_connect_fd(req, &connect);
	if (connect.error != ESP_OK) return (connect);
	return (connect);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O FD DA CONEXAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DE CONEXAO WS RECEBIDA PELO SERVIDOR
 * @param connect STRUCT QUE ESTA SENDO MONTADO POR WebSocket_connect
 * @details SALVA ESP_FAIL EM connect.error CASO O FD SEJA NEGATIVO
*/
void	WebServer::get_websocket_connect_fd(httpd_req_t *req, WebSocket_connect *connect) {
	connect->fd = httpd_req_to_sockfd(req);
	if (connect->fd < 0) connect->error = ESP_FAIL;
}

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
	if (req == NULL) {
		frame.error = ESP_ERR_INVALID_ARG;
		return (frame);
	}
	frame.error = ESP_OK;
	httpd_ws_frame_t ws_frame = {};
	esp_err_t ret = httpd_ws_recv_frame(req, &ws_frame, 0);
	if (ret != ESP_OK) {
		frame.error = ret;
		return (frame);
	}
	WebServer::get_websocket_frame_type(&ws_frame, &frame);
	WebServer::get_websocket_frame_length(&ws_frame, &frame);
	WebServer::get_websocket_frame_final(&ws_frame, &frame);
	WebServer::get_websocket_frame_payload(req, &ws_frame, &frame);
	if (frame.error != ESP_OK) return (frame);
	return (frame);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TIPO DO FRAME
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
*/
void	WebServer::get_websocket_frame_type(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	frame->type = ws_frame->type;
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TAMANHO DO FRAME
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
*/
void	WebServer::get_websocket_frame_length(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	frame->length = ws_frame->len;
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA SE JA CHEGOU NO FINAL DO FRAME
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
*/
void	WebServer::get_websocket_frame_final(httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	frame->final = ws_frame->final;
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O PAYLOAD DO FRAME
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DO FRAME WS RECEBIDA PELO SERVIDOR
 * @param ws_frame PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO WS RECEBIDA PELO SERVIDOR
 * @param frame STRUCT QUE ESTA SENDO MONTADO POR build_websocket_frame
 * @details SALVA ESP_ERR_INVALID_SIZE EM frame->error CASO O TAMANHO DO PAYLOAD ULTRAPASSE MAX_WEBSOCKET_FRAME_SIZE
 * @details SALVA ESP_ERR_NO_MEM EM frame->error CASO ws_frame->payload SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @details SALVA ret EM frame->error CASO httpd_ws_recv_frame FALHE
*/
void	WebServer::get_websocket_frame_payload(httpd_req_t *req, httpd_ws_frame_t *ws_frame, WebSocket_frame *frame) {
	if (ws_frame->len > MAX_WEBSOCKET_FRAME_SIZE) {
		frame->error = ESP_ERR_INVALID_SIZE;
		return;
	}
	if (ws_frame->len == 0) {
		frame->payload.clear();
		return;
	}
	ws_frame->payload = (uint8_t *)malloc(ws_frame->len);
	if (ws_frame->payload == NULL) {
		frame->error = ESP_ERR_NO_MEM;
		return;
	}
	esp_err_t ret = httpd_ws_recv_frame(req, ws_frame, ws_frame->len);
	if (ret == ESP_OK) frame->payload.assign(reinterpret_cast<const char *>(ws_frame->payload), ws_frame->len);
	free(ws_frame->payload);
	ws_frame->payload = NULL;
	if (ret != ESP_OK) {
		frame->error = ret;
		return;
	}
}