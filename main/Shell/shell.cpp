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
Shell::Shell(void) : logged_in(false), user(""), pwd("") {

}

/**
 * @author elguesabal
 * @brief DESTRUTOR DA CLASSE Shell
*/
Shell::~Shell(void) {

}

/**
 * @author elguesabal
 * @brief METODO QUE RECEBE UM INPUT E RETORNA A RESPOSTA
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
 * @return RETORNA UMA STRING DE RESPOSTA
*/
std::string	Shell::input_shell(std::string input) {
// INTERPRETAR O input E SEPARAR SEU COMANDO DOS ARGUMENTOS
// VERIFICAR SE JA ESTA LOGADO
// EXECUTAR OS COMANDOS
	if (input == "ls") return ("a.out VampetaOS.c\n");
	if (input == "pwd") return ("/VampetaOS/\n");
	if (input == "echo VampetaOS") return ("VampetaOS\n");
	return ("Command not found\n");
}