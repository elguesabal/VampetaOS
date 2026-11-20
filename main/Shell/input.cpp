/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/authentication.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  task_shell                                                                |
  |  input_shell                                                               |
  |  run                                                                       |
  |  parse_input                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

void	Shell::task_shell(void *arg) {
	// Shell *shell = static_cast<Shell *>(arg);
	// while (true) {
	// 	std::string input;
	// 	if (xQueueReceive(shell->queue, &input, portMAX_DELAY) == pdPASS) shell->run(input);
	// }



    Shell *shell = static_cast<Shell *>(arg);
    while (true) {
        char input[SHELL_INPUT_MAX];
        if (xQueueReceive(shell->queue, input, portMAX_DELAY) == pdPASS) shell->run(input);
    }
}

// void	Shell::input_shell(std::string input) {
// 	xQueueSend(queue, &input, portMAX_DELAY);
// }
void	Shell::input_shell(const char *input) {
	// xQueueSend(queue, &input, portMAX_DELAY);



	if (input == nullptr) return;
	size_t len = strlen(input);
	if (len >= SHELL_INPUT_MAX) return;
	char buffer[SHELL_INPUT_MAX] = {};
	memcpy(buffer, input, len);
	xQueueSend(queue, buffer, 0);
}

			void	print_command(const Command &command) {
				printf("command.command ---> %s\n", command.command.c_str());
				printf("command.args ---> { ");
				for (size_t i = 0; i < command.args.size(); i++) {
					printf("%s", command.args[i].c_str());
					if (i + 1 < command.args.size()) printf(", ");
				}
				printf(" }\n");
			}
/**
 * @author elguesabal
 * @brief METODO QUE RECEBE UM INPUT E RETORNA A RESPOSTA
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
*/
void	Shell::run(std::string input) {
// INTERPRETAR O input E SEPARAR SEU COMANDO DOS ARGUMENTOS
	if (!this->parse_input(input)) {
		this->emit_output("FINISHED", "ERROR INPUT\n");
		return;
	}
print_command(command);
// VERIFICAR SE JA ESTA LOGADO
	if (!this->check_authentication()) {
		this->emit_output("FINISHED", "Access denied: no active user session.\nPlease authenticate using \"login\" or create an account using \"useradd\".\n");
		return;
	}
// EXECUTAR OS COMANDOS



	if (this->command.command == "useradd") this->useradd();
	else if (this->command.command == "login") this->login();
	else if (this->command.command == "echo") this->echo();
	else if (this->command.command == "ls") this->emit_output("FINISHED", "a.out VampetaOS.c\n");
	else if (this->command.command == "pwd") this->emit_output("FINISHED", "/VampetaOS/\n");
	else if (this->command.command == "echo VampetaOS") this->emit_output("FINISHED", "VampetaOS\n");
	else this->emit_output("FINISHED", "Command not found\n");
// DEVO ME PREOCUPAR COM A FORMA QUE FACO O ENVIO DO OUTPUT E PERMITIR QUE SEJA ENVIADA POR PARTES
// TALVEZ EU CRIE UM MECANISMO DE ENVIO POR PARTES DENTRO DO PROPRIO Shell USANDO JSON
}

/**
 * @author elguesabal
 * @brief INTERPRETA A ENTRADA RECEBIDA E SEPARA O COMANDO DOS SEUS ARGUMENTOS
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
 * @return RETORNA true CASO A INTERPRETACAO SEJA REALIZADA COM SUCESSO
 * @return RETORNA false CASO A ENTRADA SEJA VAZIA OU NAO CONTENHA UM COMANDO VALIDO
*/
bool	Shell::parse_input(std::string &input) {
	this->command.clear();
	if (input.empty()) return (false);
	size_t pos;
	while ((pos = input.find(' ')) != std::string::npos) {
		std::string arg = input.substr(0, pos);
		if (!arg.empty()) this->command.args.push_back(arg);
		input.erase(0, pos + 1);
	}
	if (!input.empty()) this->command.args.push_back(input);
	if (this->command.args.empty()) return (false);
	this->command.command = this->command.args[0];
	this->command.args.erase(this->command.args.begin());
	return (true);
}