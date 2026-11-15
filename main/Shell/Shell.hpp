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
 * @brief STRUCT RESPONSAVEL POR ORGANIZAR OS COMANDOS E ARGUMENTOS
*/
struct Command {
	std::string					command;
	std::vector<std::string>	args;

	/**
	 * @author elguesabal
	 * @brief METODO RESPONSAVEL POR LIMPAR O COMMAND
	*/
	void	clear(void) {
		this->command.clear();
		this->args.clear();
	}
};

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
		Command				command;

	public:
		// /Shell/shell.cpp
		static bool	init_shell(void);
		Shell(void);
		~Shell(void);

		// /Shell/input.cpp
		std::string	input_shell(std::string input);

	private:
		// /Shell/directory.cpp
		static bool	check_dir(void);

		// /Shell/input.cpp
		bool		parse_input(std::string &input);

		// /Shell/authentication.cpp
		bool		check_authentication(void);

		// /Shell/commands/useradd.cpp
		std::string	useradd(void);

		// /Shell/commands/login.cpp
		std::string	login(void);

		// /Shell/commands/echo.cpp
		std::string	echo(void);
};

#endif