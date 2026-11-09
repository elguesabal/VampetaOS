/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/shell.cpp                                                          |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |                                                                            |
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
	printf("Shell: OK\n");
	return (true);
}


std::string Shell::shell(std::string command) {
	if (command == "ls") return ("a.out VampetaOS.c\n");
	if (command == "pwd") return ("/VampetaOS/\n");
	if (command == "echo VampetaOS") return ("VampetaOS\n");
	return ("Command not found\n");
}




// WebShell::WebShell() {

// }

// void  run_command(void) {

// }