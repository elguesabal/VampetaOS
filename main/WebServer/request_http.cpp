/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebServer/request_http.cpp                                               |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  build_request_http                                                        |
  |  get_request_method                                                        |
  |  get_request_path                                                          |
  |  get_request_query                                                         |
  |  get_request_content_type                                                  |
  |  get_request_content_length                                                |
  |  get_request_body                                                          |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE INTERPRETA UMA REQUISICAO HTTP E SALVA E RETORNA UM STRUCT Resquest_http
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA UM Resquest_http COMPLETO EM CASO DA REQUISICAO FOR VALIDA
 * @return RETORNA UM Resquest_http VAZIO CASO req SEJA NULL
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_query FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_content_type FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_body FALHE
*/
Resquest_http	WebServer::build_request_http(httpd_req_t *req) {
	Resquest_http request = {};
	if (req == NULL) {
		request.error = ESP_ERR_INVALID_ARG;
		return (request);
	}
	request.error = ESP_OK;
	WebServer::get_request_method(req, &request);
	WebServer::get_request_path(req, &request);
	WebServer::get_request_query(req, &request);
	if (request.error != ESP_OK) return (request);
	WebServer::get_request_content_type(req, &request);
	if (request.error != ESP_OK) return (request);
	WebServer::get_request_content_length(req, &request);
	WebServer::get_request_body(req, &request);
	if (request.error != ESP_OK) return (request);
	return (request);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O METODO DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
*/
void	WebServer::get_request_method(httpd_req_t *req, Resquest_http *request) {
	request->method = static_cast<httpd_method_t>(req->method);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O PATH DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
*/
void	WebServer::get_request_path(httpd_req_t *req, Resquest_http *request) {
	request->path = req->uri;
	size_t pos = request->path.find('?');
	if (pos != std::string::npos) request->path.erase(pos);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA A QUERY DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @details SALVA ESP_ERR_NO_MEM EM request->error CASO buffer SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @details SALVA ret EM request->error CASO httpd_req_get_url_query_str FALHE
*/
void	WebServer::get_request_query(httpd_req_t *req, Resquest_http *request) {
	size_t len = httpd_req_get_url_query_len(req);
	if (len == 0) return;
	char *buffer = (char *)malloc(len + 1);
	if (buffer == NULL) {
		request->error = ESP_ERR_NO_MEM;
		return;
	}
	esp_err_t ret = httpd_req_get_url_query_str(req, buffer, len + 1);
	if (ret == ESP_OK) {
		request->query = buffer;
	} else {
		request->error = ret;
	}
	free(buffer);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TIPO DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @details SALVA ESP_ERR_NO_MEM EM request->error CASO buffer SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @details SALVA ret EM request->error CASO httpd_req_get_hdr_value_str FALHE
*/
void	WebServer::get_request_content_type(httpd_req_t *req, Resquest_http *request) {
	size_t len = httpd_req_get_hdr_value_len(req, "Content-Type");
	if (len == 0) return;
	char *buffer = (char *)malloc(len + 1);
	if (buffer == NULL) {
		request->error = ESP_ERR_NO_MEM;
		return;
	}
	esp_err_t ret = httpd_req_get_hdr_value_str(req, "Content-Type", buffer, len + 1);
	if (ret == ESP_OK) {
		request->content_type = buffer;
	} else {
		request->error = ret;
	}
	free(buffer);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TAMANHO DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
*/
void	WebServer::get_request_content_length(httpd_req_t *req, Resquest_http *request) {
	request->content_length = req->content_len;
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O BODY DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @details SALVA ESP_ERR_INVALID_SIZE EM request->error CASO O TAMANHO DO PAYLOAD ULTRAPASSE MAX_REQUEST_BODY_SIZE
 * @details SALVA ESP_FAIL EM request->error CASO OCORRA UMA FALHA AO RECEBER O BODY DA REQUISICAO
*/
void	WebServer::get_request_body(httpd_req_t *req, Resquest_http *request) {
	if (req->content_len > MAX_REQUEST_BODY_SIZE) {
		request->error = ESP_ERR_INVALID_SIZE;
		return;
	}
	char buffer[256];
	size_t remaining = req->content_len;
	while (remaining > 0) {
		size_t chunk = (remaining < sizeof(buffer)) ? remaining : sizeof(buffer);
		int received = httpd_req_recv(req, buffer, chunk);
		if (received == HTTPD_SOCK_ERR_TIMEOUT) continue;
		if (received <= 0 || (size_t)received > chunk) {
			request->error = ESP_FAIL;
			return;
		}
		request->body.append(buffer, received);
		remaining -= received;
	}
}