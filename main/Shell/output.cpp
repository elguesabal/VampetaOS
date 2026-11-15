/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/output.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  emit_output                                                               |
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
}

/**
 * @author elguesabal
 * @brief 
 * @param input
 * @return RETORNA UMA STRING DE RESPOSTA
 * @return RETORNA UMA STRING VAZIA CASO input SEJA nullptr
*/
std::string Shell::json_escape(const char *input) {
    std::string output;
    if (input == nullptr) return (output);
    while (*input) {
        switch (*input) {
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
                if (static_cast<unsigned char>(*input) < 0x20) {
                    output += "?";
				} else {
                    output += *input;
				}
                break;
        }
        input++;
    }
    return (output);
}

// OUTPUT
// INPUT
// FINISHED