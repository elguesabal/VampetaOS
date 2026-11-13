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
#include "Command.hpp"
#include "UserManager/UserManager.hpp"

// /**
//  * @author elguesabal
//  * @brief STRUCT RESPONSAVEL POR ORGANIZAR OS COMANDOS E ARGUMENTOS
// */
// struct Command {
// 	std::string					command;
// 	std::vector<std::string>	args;
// };

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O SHELL
*/
class Shell {
	private:
		// bool				logged_in;
		// bool				sudo;
		// std::string			user;
		std::string			pwd;
		// std::vector<std::string>	environment;
		UserManager			user_manager;

	public:
		// /Shell/shell.cpp
		static bool			init_shell(void);
		Shell(void);
		~Shell(void);
		std::string			input_shell(std::string input);
		bool				parse_input(std::string &input, Command &command);

	private:
		// /Shell/directory.cpp
		static bool			check_dir(void);
};

#endif