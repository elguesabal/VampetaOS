/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/commnads/echo.cpp                                                  |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  echo                                                                      |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "../Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO RESPONSAVEL PELO COMANDO echo
 * @return RETORNA UMA STRING DE RESPOSTA
*/
std::string	Shell::echo(void) {
	std::string ret;
	for (int i = 0; i < this->command.args.size(); i++) ret += this->command.args[i] + " ";
	ret += "\n";
	return (ret);
}