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
 * @param port PORTA DA CONEXAO
 * @param fd FILE DESCRIPTION DA CONEAXO
*/
Shell::Shell(uint16_t port, int fd) : port(port), fd(fd), logged_in(false), user(""), pwd(""), command() {

}

/**
 * @author elguesabal
 * @brief DESTRUTOR DA CLASSE Shell
*/
Shell::~Shell(void) {

}