/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/authentication.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  check_authentication                                                      |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE O LOGIN ESTA FEITO E QUAIS COMANDOS ESTAO DISPONIVEIS EM CASO DE NAO LOGADO
 * @return RETORNA true ESTEJA LOGADO
 * @return RETORNA true NAO ESTEJA LOGADO E O COMANDO SEJA login
 * @return RETORNA true NAO ESTEJA LOGADO E O COMANDO SEJA useradd
 * @return RETORNA false NAO ESTEJA LOGADO E NOA SEJA NENHUM COMANDO MENCIONADO ACIMA
*/
bool	Shell::check_authentication(void) {
	if (this->logged_in) return (true);
	if (this->command.command == "login") return (true);
	if (this->command.command == "useradd") return (true);
	return (false);
}