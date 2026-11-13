/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/Command.hpp                                                        |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../VampetaOS.hpp"

/**
 * @author elguesabal
 * @brief STRUCT RESPONSAVEL POR ORGANIZAR OS COMANDOS E ARGUMENTOS
*/
struct Command {
	std::string					command;
	std::vector<std::string>	args;
};

#endif