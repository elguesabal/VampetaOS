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
		uint16_t			port;
		int					fd;
TaskHandle_t		task;
QueueHandle_t		queue;
		bool				logged_in;
		// bool				sudo;
		std::string			user;
		std::string			pwd;
		// std::vector<std::string>	environment;
		Command				command;

	public:
		// /Shell/shell.cpp
		static bool	init_shell(void);
		Shell(uint16_t port, int fd);
		~Shell(void);

		// /Shell/input.cpp
static void	task_shell(void *arg);
		void		input_shell(std::string input);
void		run(std::string input);

	private:
		// /Shell/directory.cpp
		static bool	check_dir(void);

		// /Shell/input.cpp
		bool		parse_input(std::string &input);

		// /Shell/output.cpp
		void		emit_output(const char *type, const char *output);
		std::string	json_escape(const char *input);

		// /Shell/authentication.cpp
		bool		check_authentication(void);

		// /Shell/commands/useradd.cpp
		void		useradd(void);

		// /Shell/commands/login.cpp
		void		login(void);

		// /Shell/commands/echo.cpp
		void		echo(void);
};

#endif