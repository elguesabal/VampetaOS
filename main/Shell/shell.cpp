/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/shell.cpp                                                          |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_shell                                                                |
  |  Shell                                                                     |
  |  ~Shell                                                                    |
  |  input_shell                                                               |
  |  parse_input                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief INICIA O SHELL
 * @return RETORNA true EM CASO DO SHELL INICIADO COM SUCESSO
 * @return RETORNA false CASO ??? FALHE
*/
bool	Shell::init_shell(void) {
	if (!Shell::check_dir()) return (false);
	printf("Shell: OK\n");
	return (true);
}

/**
 * @author elguesabal
 * @brief CONSTRUTOR DA CLASSE Shell
*/
// Shell::Shell(void) : logged_in(false), user(""), pwd("") {
Shell::Shell(void) : pwd(""), user_manager() {

}

/**
 * @author elguesabal
 * @brief DESTRUTOR DA CLASSE Shell
*/
Shell::~Shell(void) {

}

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
	Command command;
// INTERPRETAR O input E SEPARAR SEU COMANDO DOS ARGUMENTOS
	if (!this->parse_input(input, command)) return ("ERROR INPUT\n");
print_command(command);
// VERIFICAR SE JA ESTA LOGADO
	// if (!UserManager::user_manager(command)) return ("ERROR UserManager\n");
	if (!this->user_manager.user_manager(command)) return ("ERROR UserManager\n");
// EXECUTAR OS COMANDOS



	if (command.command == "ls") return ("a.out VampetaOS.c\n");
	if (command.command == "pwd") return ("/VampetaOS/\n");
	if (command.command == "echo VampetaOS") return ("VampetaOS\n");
	return ("Command not found\n");
}

/**
 * @author elguesabal
 * @brief INTERPRETA A ENTRADA RECEBIDA E SEPARA O COMANDO DOS SEUS ARGUMENTOS
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
 * @param command STRUCT QUE ARMAZENA O NOME DO COMANDO E SEUS ARGUMENTOS
 * @return RETORNA true CASO A INTERPRETACAO SEJA REALIZADA COM SUCESSO
 * @return RETORNA false CASO A ENTRADA SEJA VAZIA OU NAO CONTENHA UM COMANDO VALIDO
*/
bool	Shell::parse_input(std::string &input, Command &command) {
	if (input.empty()) return (false);
	size_t pos;
	while ((pos = input.find(' ')) != std::string::npos) {
		std::string arg = input.substr(0, pos);
		if (!arg.empty()) command.args.push_back(arg);
		input.erase(0, pos + 1);
	}
	if (!input.empty()) command.args.push_back(input);
	if (command.args.empty()) return (false);
	command.command = command.args[0];
	command.args.erase(command.args.begin());
	return (true);
}