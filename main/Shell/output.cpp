/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/output.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  emit_output                                                               |
  |  json_escape                                                               |
  |                                                                            |
  |                                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
* @author elguesabal
* @brief METODO RESPONSAVEL POR FAZER O ENVIO DE UMA MENSAGEM
* @param type TIPO DA RESPOSTA
* @param output TEXTO A SER PRINTADO NO FRONT END
* @details PARA O CODIGO CASO type SEJA nullptr
* @details PARA O CODIGO CASO output SEJA nullptr
*/
void	Shell::emit_output(const char *type, const char *output) {
	if (type == nullptr || output == nullptr) return;
	std::string json;
	json += "{\"type\":\"";
	json += type;
	json += "\",\"output\":\"";
	json += Shell::json_escape(output);
	if (strcmp(type, "FINISHED") == 0) json += "elguesabal@VampetaOS:~$ ";
	json += "\"}";
printf("%s\n", json.c_str());
	WebServer::send_text_ws_fd(this->port, this->fd, json.c_str());
// OUTPUT
// INPUT
// FINISHED
}

/**
* @author elguesabal
* @brief FAZ UMA MODIFICACAO NO TEXTO QUE DEVE SER ENVIADO PARA SER INTERPRETADO CORRETAMENTE CARACTERES DE ESCAPE
* @param text TEXTO A SER MODIFICADO
* @return RETORNA UMA STRING DE RESPOSTA
* @return RETORNA UMA STRING VAZIA CASO text SEJA nullptr
*/
std::string Shell::json_escape(const char *text) {
	std::string output;
	if (text == nullptr) return (output);
	while (*text) {
		switch (*text) {
			case '"':
				output += "\\\"";
				break;
			case '\\':
				output += "\\\\";
				break;
			case '\b':
				output += "\\b";
				break;
			case '\f':
				output += "\\f";
				break;
			case '\n':
				output += "\\n";
				break;
			case '\r':
				output += "\\r";
				break;
			case '\t':
				output += "\\t";
				break;
			default:
				if (static_cast<unsigned char>(*text) < 0x20) {
					output += "?";
				} else {
					output += *text;
				}
				break;
		}
		text++;
	}
	return (output);
}



/**
* @author elguesabal
* @brief ENVIA UMA STRING COMO RESPOSTA AO WEBSOCKET OU ESCREVE EM UM ARQUIVO
* @param fd FILE DESCRIPTION QUE SERA ESCRITO
* @param buffer STRING QUE SERA ESCRITA
* @param size TAMANHO DE buffer
* @return RETORNA O TAMANHO DA STRING ENVIADA AO WEBSOCKET OU ESCRITA NO FD
* @return RETORNA 0 CASO sizer FOR 0
* @return RETORNA -1 CASO buffer SER nullptr
*/
ssize_t Shell::write(int fd, const void *buffer, size_t size) {
	if (buffer == nullptr && size > 0) {
		errno = EFAULT;
		return (-1);
	}
	if (size == 0) return (0);
	if (this->fd == fd) {
		std::string text(static_cast<const char *>(buffer), size);
		esp_err_t ret = WebServer::send_text_ws_fd(this->port, fd, text.c_str());
		if (ret != ESP_OK) {
			errno = EIO;
			return (-1);
		}
		return (size);
	}
	return (::write(fd, buffer, size));
}

// void    Shell::printf() {

// }