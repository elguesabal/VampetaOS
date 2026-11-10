/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/Shell.hpp                                                          |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef SHELL_H
#define SHELL_H

#include "../VampetaOS.hpp"
#include "../Sd/Sd.hpp"
#include "../WebServer/WebServer.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O SHELL
*/
class Shell {
	// private:
	// 	bool				logged_in = false;
	// 	bool				adm;
	// 	std::string			user;
	// 	std::string			pwd;

	public:
		// /Shell/shell.cpp
		static bool			init_shell(void);
		static std::string	shell(std::string command);

	private:
		// /Shell/directory.cpp
		static bool			check_dir(void);
};

#endif