/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
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

			void	print_command(const Command &command) {
				printf("command.command ---> %s\n", command.command.c_str());
				printf("command.args ---> { ");
				for (size_t i = 0; i < command.args.size(); i++) {
					printf("%s", command.args[i].c_str());
					if (i + 1 < command.args.size()) printf(", ");
				}
				printf(" }\n");
			}
/**
 * @author elguesabal
 * @brief METODO QUE RECEBE UM INPUT E RETORNA A RESPOSTA
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
 * @return RETORNA UMA STRING DE RESPOSTA
*/
std::string	Shell::input_shell(std::string input) {
// INTERPRETAR O input E SEPARAR SEU COMANDO DOS ARGUMENTOS
	if (!this->parse_input(input)) return ("ERROR INPUT\n");
print_command(command);
// VERIFICAR SE JA ESTA LOGADO
	if (!this->check_authentication()) return ("Access denied: no active user session.\nPlease authenticate using \"login\" or create an account using \"useradd\".\n");
// EXECUTAR OS COMANDOS



	if (this->command.command == "useradd") return (this->useradd());
	if (this->command.command == "login") return (this->login());
	if (this->command.command == "echo") return (this->echo());
	if (this->command.command == "ls") return ("a.out VampetaOS.c\n");
	if (this->command.command == "pwd") return ("/VampetaOS/\n");
	if (this->command.command == "echo VampetaOS") return ("VampetaOS\n");
	return ("Command not found\n");
// DEVO ME PREOCUPAR COM A FORMA QUE FACO O ENVIO DO OUTPUT E PERMITIR QUE SEJA ENVIADA POR PARTES
// TALVEZ EU CRIE UM MECANISMO DE ENVIO POR PARTES DENTRO DO PROPRIO Shell USANDO JSON
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