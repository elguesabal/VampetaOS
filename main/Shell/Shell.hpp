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

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O SHELL
*/
class Shell {
	private:
		bool				logged_in;
		// bool				sudo;
		std::string			user;
		std::string			pwd;
		// std::vector<std::string>	environment;

	public:
		// /Shell/shell.cpp
		static bool			init_shell(void);
		Shell(void);
		~Shell(void);
		std::string			input_shell(std::string input);

	private:
		// /Shell/directory.cpp
		static bool			check_dir(void);
};

#endif