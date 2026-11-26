/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/authentication.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  input_shell                                                               |
  |  parse_input                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE RECEBE A NOTIFICACAO DE UM FRAME E ENVIA O COMANDO PARA A TASK RESOLVER DE FORMA ṔARALELA
 * @param input STRING RECEBIDA DO WEBSOCKET
*/
void	Shell::input_shell(const char *input) {
	if (input == nullptr) return;
	size_t len = strlen(input);
	if (len >= SHELL_INPUT_MAX) {
		this->printf("SHELL_INPUT_MAX\n");
		return;
	}
	char buffer[SHELL_INPUT_MAX] = {};
	memcpy(buffer, input, len);
	xQueueSend(queue, buffer, 0);
}

/**
 * @author elguesabal
 * @brief INTERPRETA A ENTRADA RECEBIDA E SEPARA O COMANDO DOS SEUS ARGUMENTOS
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
 * @return RETORNA true CASO A INTERPRETACAO SEJA REALIZADA COM SUCESSO
 * @return RETORNA false CASO A ENTRADA SEJA VAZIA OU NAO CONTENHA UM COMANDO VALIDO
*/
bool	Shell::parse_input(std::string &input) {
	this->command.clear();
	if (input.empty()) return (false);
	size_t pos;
	while ((pos = input.find(' ')) != std::string::npos) {
		std::string arg = input.substr(0, pos);
		if (!arg.empty()) this->command.args.push_back(arg);
		input.erase(0, pos + 1);
	}
	if (!input.empty()) this->command.args.push_back(input);
	if (this->command.args.empty()) return (false);
	this->command.command = this->command.args[0];
	this->command.args.erase(this->command.args.begin());
	return (true);
}