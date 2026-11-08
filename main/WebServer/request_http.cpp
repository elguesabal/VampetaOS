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
  |  get_request_body                                                          |
  |  get_request_content_type                                                  |
  |  get_request_content_length                                                |
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
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_method FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_path FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_query FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_content_type FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_content_length FALHE
 * @return RETORNA UM Resquest_http INCOMPLETO CASO get_request_body FALHE
*/
Resquest_http	WebServer::build_request_http(httpd_req_t *req) {
	Resquest_http request = {};
	request.valid = false;
	if (req == NULL) return (request);
	if (!WebServer::get_request_method(req, &request)) return (request);
	if (!WebServer::get_request_path(req, &request)) return (request);
	if (!WebServer::get_request_query(req, &request)) return (request);
	if (!WebServer::get_request_content_type(req, &request)) return (request);
	if (!WebServer::get_request_content_length(req, &request)) return (request);
	if (!WebServer::get_request_body(req, &request)) return (request);
	request.valid = true;
	return (request);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O METODO DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @return RETORNA true CASO O METODO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO request SEJA NULL
*/
bool	WebServer::get_request_method(httpd_req_t *req, Resquest_http *request) {
	if (req == NULL || request == NULL) return (false);
	request->method = static_cast<httpd_method_t>(req->method);
	return (true);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O PATH DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @return RETORNA true CASO O PATH SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO request SEJA NULL
*/
bool	WebServer::get_request_path(httpd_req_t *req, Resquest_http *request) {
	if (req == NULL || request == NULL) return (false);
	request->path = req->uri;
	size_t pos = request->path.find('?');
	if (pos != std::string::npos) request->path.erase(pos);
	return (true);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA A QUERY DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @return RETORNA true CASO A QUERY SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO request SEJA NULL
 * @return RETORNA false CASO httpd_req_get_url_query_len FALHE
 * @return RETORNA false CASO buffer SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @return RETORNA false CASO httpd_req_get_url_query_str FALHE
*/
bool	WebServer::get_request_query(httpd_req_t *req, Resquest_http *request) {
	if (req == NULL || request == NULL) return (false);
	size_t len = httpd_req_get_url_query_len(req);
	if (len == 0) return (true);
	char *buffer = (char *)malloc(len + 1);
	if (buffer == NULL) return (false);
	esp_err_t ret = httpd_req_get_url_query_str(req, buffer, len + 1);
	if (ret == ESP_OK) request->query = buffer;
	free(buffer);
	return (ret == ESP_OK);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O BODY DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @return RETORNA true CASO O BODY SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO request SEJA NULL
 * @return RETORNA false CASO O TAMANHO DO BODY ULTRAPASSE MAX_REQUEST_BODY_SIZE
 * @return RETORNA false CASO OCORRA UMA FALHA AO RECEBER O BODY DA REQUISICAO
*/
bool	WebServer::get_request_body(httpd_req_t *req, Resquest_http *request) {
	if (req == NULL || request == NULL) return (false);
	if (req->content_len > MAX_REQUEST_BODY_SIZE) return (false);
	char buffer[256];
	size_t remaining = req->content_len;
	while (remaining > 0) {
		size_t chunk = (remaining < sizeof(buffer)) ? remaining : sizeof(buffer);
		int received = httpd_req_recv(req, buffer, chunk);
		if (received == HTTPD_SOCK_ERR_TIMEOUT) continue;
		if (received <= 0 || (size_t)received > chunk) return (false);
		request->body.append(buffer, received);
		remaining -= received;
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TIPO DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @return RETORNA true CASO O TIPO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO request SEJA NULL
 * @return RETORNA false CASO httpd_req_get_hdr_value_len FALHE
 * @return RETORNA false CASO buffer SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @return RETORNA false CASO httpd_req_get_hdr_value_str FALHE
*/
bool	WebServer::get_request_content_type(httpd_req_t *req, Resquest_http *request) {
	if (req == NULL || request == NULL) return (false);
	size_t len = httpd_req_get_hdr_value_len(req, "Content-Type");
	if (len == 0) return (true);
	char *buffer = (char *)malloc(len + 1);
	if (buffer == NULL) return (false);
	esp_err_t ret = httpd_req_get_hdr_value_str(req, "Content-Type", buffer, len + 1);
	if (ret == ESP_OK) request->content_type = buffer;
	free(buffer);
	return (ret == ESP_OK);
}

/**
 * @author elguesabal
 * @brief INTERPRETA E SALVA O TAMANHO DA REQUISICAO
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @param request STRUCT QUE ESTA SENDO MONTADO POR build_request_http
 * @return RETORNA true CASO O TAMANHO DA REQUISICAO SEJA SALVO NO STRUCT
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO request SEJA NULL
*/
bool	WebServer::get_request_content_length(httpd_req_t *req, Resquest_http *request) {
	if (req == NULL || request == NULL) return (false);
	request->content_length = req->content_len;
	return (true);
}