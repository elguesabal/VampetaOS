/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebShell/WebShell.hpp                                                    |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef WEBSHELL_H
#define WEBSHELL_H

#include "../VampetaOS.hpp"
#include "../WebServer/WebServer.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WEBSHELL
*/
class WebShell {
	public:
		static std::string shell(std::string command);
};

#endif