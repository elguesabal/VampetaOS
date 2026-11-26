/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
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

#define SHELL_INPUT_MAX 256
#define OUTPUT_WEBSOCKET 0
#define OUTPUT_FILE 1
#define OUTPUT_SERIAL 2	// VOU USAR???

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
		int					fd_output;
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
		Shell(const WebSocket_connect &connect);
		~Shell(void);
		bool		is_initialized(void) const;

		// /Shell/input.cpp
		void		input_shell(const char *input);

	private:
		// /Shell/directory.cpp
		static bool	check_dir(void);

		// /Shell/task.cpp
		esp_err_t	wellcome_shell(void);
		static void	task_shell(void *arg);
		void		run(std::string input);
		void		stop_task_shell(void);

		// /Shell/input.cpp
		bool		parse_input(std::string &input);

		// /Shell/output.cpp
		// void		emit_output(const char *type, const char *output);
		// std::string	json_escape(const char *input);
		ssize_t		write(int fd, const void *buffer, size_t size);
		int			printf(const char *format, ...);

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