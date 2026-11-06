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
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebServer.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE INTERPRETA UMA REQUISICAO HTTP E SALVA E RETORNA UM STRUCT Resquest_http
 * @param req PONTEIRO PARA ESTRUTURA QUE CONTEM AS INFORMACOES DA REQUISICAO HTTP RECEBIDA PELO SERVIDOR
 * @return RETORNA true EM CASO DA REQUISICAO FOR VALIDA E RETORNAR UM Resquest_http
 * @return RETORNA false CASO req SEJA NULL
 * @return RETORNA false CASO O TAMANHO DO BODY ULTRAPASSE MAX_REQUEST_BODY_SIZE
 * @return RETORNA false CASO query SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @return RETORNA false CASO httpd_req_get_url_query_str FALHE
 * @return RETORNA false CASO content_type SEJA NULL AO TENTAR ALOCAR MEMORIA
 * @return RETORNA false CASO httpd_req_get_hdr_value_str FALHE
 * @return RETORNA false CASO OCORRA UMA FALHA AO RECEBER O BODY DA REQUISICAO
*/
Resquest_http	WebServer::build_request_http(httpd_req_t *req) {
	Resquest_http request = {};
	request.valid = false;
	if (req == NULL) return (request);
	request.method = static_cast<httpd_method_t>(req->method);
	request.path = req->uri;
	size_t pos = request.path.find('?');
	if (pos != std::string::npos) request.path.erase(pos);
	request.content_length = req->content_len;
	if (req->content_len > MAX_REQUEST_BODY_SIZE) return (request);
	size_t query_len = httpd_req_get_url_query_len(req);
	if (query_len > 0) {
		char *query = (char *)malloc(query_len + 1);
		if (query == NULL) return (request);
		esp_err_t ret = httpd_req_get_url_query_str(req, query, query_len + 1);
		if (ret != ESP_OK) {
			free(query);
			return (request);
		}
		request.query = query;
		free(query);
	}
	size_t type_len = httpd_req_get_hdr_value_len(req, "Content-Type");
	if (type_len > 0) {
		char *content_type = (char *)malloc(type_len + 1);
		if (content_type == NULL) return (request);
		esp_err_t ret = httpd_req_get_hdr_value_str(req, "Content-Type", content_type, type_len + 1);
		if (ret != ESP_OK) {
			free(content_type);
			return (request);
		}
		request.content_type = content_type;
		free(content_type);
	}
	char buffer[256];
	size_t remaining = req->content_len;
	while (remaining > 0) {
		size_t chunk = (remaining < sizeof(buffer)) ? remaining : sizeof(buffer);
		int received = httpd_req_recv(req, buffer, chunk);
		if (received == HTTPD_SOCK_ERR_TIMEOUT) continue;
		if (received <= 0) return (request);
		request.body.append(buffer, received);
		remaining -= received;
	}
	request.valid = true;
	return (request);
}