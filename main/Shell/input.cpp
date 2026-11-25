/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/authentication.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  wellcome_shell                                                            |
  |  task_shell                                                                |
  |  input_shell                                                               |
  |  run                                                                       |
  |  parse_input                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE ENVIA A MENSAGEM DE BOAS VINDAS DO TERMINAL
*/
esp_err_t	Shell::wellcome_shell(void) {
	extern const uint8_t ascii_art_start[] asm("_binary_ascii_art_start");
	extern const uint8_t ascii_art_end[] asm("_binary_ascii_art_end");
	size_t len = ascii_art_end - ascii_art_start;
	char *ascii_art = new (std::nothrow) char[len + 1];
	if (ascii_art == nullptr) return (ESP_ERR_NO_MEM);
	memcpy(ascii_art, ascii_art_start, len);
	ascii_art[len] = '\0';
	esp_err_t ret = WebServer::send_text_ws_fd(this->port, this->fd, ascii_art);
	delete[] ascii_art;
	if (ret != ESP_OK) return (ret);
	return (ESP_OK);
}

/**
 * @author elguesabal
 * @brief METODO QUE SERA USADO COMO HANDLER PARA A TASK DE EXECUCAO DE COMANDOS DOS SHELL
 * @param arg ARGUMENTO PASSADO NA CRIACAO DA TASK (ESSE ARGUMENTO RECEBE this DA PROPRIA CLASSE)
*/
void	Shell::task_shell(void *arg) {
	Shell *shell = static_cast<Shell *>(arg);
	if (shell->wellcome_shell() != ESP_OK) vTaskDelete(NULL);
	while (true) {
		if (WebServer::send_text_ws_fd(shell->port, shell->fd, "elguesabal@VampetaOS:~$ ") != ESP_OK) break;
		char input[SHELL_INPUT_MAX];
		if (xQueueReceive(shell->queue, input, portMAX_DELAY) != pdPASS) {
			WebServer::send_text_ws_fd(shell->port, shell->fd, "ERROR INPUT");
			break;
		}
		shell->run(input);
	}
	vTaskDelete(NULL);
}

/**
 * @author elguesabal
 * @brief METODO QUE RECEBE A NOTIFICACAO DE UM FRAME E ENVIA O COMANDO PARA A TASK RESOLVER DE FORMA ṔARALELA
 * @param input STRING RECEBIDA DO WEBSOCKET
*/
void	Shell::input_shell(const char *input) {
	if (input == nullptr) return;
	size_t len = strlen(input);
	if (len >= SHELL_INPUT_MAX) {
		// this->emit_output("FINISHED", "SHELL_INPUT_MAX\n");
WebServer::send_text_ws_fd(this->port, this->fd, "SHELL_INPUT_MAX\n");
		return;
	}
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
 * @brief METODO QUE RECEBE O INPUT E EXECUTA O COMANDO (METODO CHAMADO POR task_shell)
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
*/
void	Shell::run(std::string input) {
// INTERPRETAR O input E SEPARAR SEU COMANDO DOS ARGUMENTOS
	if (!this->parse_input(input)) {
		// this->emit_output("FINISHED", "ERROR INPUT\n");
WebServer::send_text_ws_fd(this->port, this->fd, "ERROR INPUT\n");
		return;
	}
print_command(command);
// VERIFICAR SE JA ESTA LOGADO
	if (!this->check_authentication()) {
		// this->emit_output("FINISHED", "Access denied: no active user session.\nPlease authenticate using \"login\" or create an account using \"useradd\".\n");
WebServer::send_text_ws_fd(this->port, this->fd, "Access denied: no active user session.\nPlease authenticate using \"login\" or create an account using \"useradd\".\n");
		return;
	}
// EXECUTAR OS COMANDOS



	if (this->command.command == "useradd") this->useradd();
	else if (this->command.command == "login") this->login();
	else if (this->command.command == "echo") this->echo();
	// else if (this->command.command == "ls") this->emit_output("FINISHED", "a.out VampetaOS.c\n");
else if (this->command.command == "ls") WebServer::send_text_ws_fd(this->port, this->fd, "a.out VampetaOS.c\n");
	// else if (this->command.command == "pwd") this->emit_output("FINISHED", "/VampetaOS/\n");
else if (this->command.command == "pwd") WebServer::send_text_ws_fd(this->port, this->fd, "/VampetaOS/\n");
	// else if (this->command.command == "echo VampetaOS") this->emit_output("FINISHED", "VampetaOS\n");
else if (this->command.command == "echo VampetaOS") WebServer::send_text_ws_fd(this->port, this->fd, "VampetaOS\n");
	// else this->emit_output("FINISHED", "Command not found\n");
else WebServer::send_text_ws_fd(this->port, this->fd, "Command not found\n");
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