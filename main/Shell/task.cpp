/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/task.cpp                                                           |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  wellcome_shell                                                            |
  |  task_shell                                                                |
  |  run                                                                       |
  |  stop_task_shell                                                           |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO QUE ENVIA A MENSAGEM DE BOAS VINDAS DO TERMINAL
 * @return RETORNA ESP_OK CASO A MENSAGEM DE BOAS VINDAS SEJA ENVIADA COM SUCESSO
 * @return RETORNA ESP_ERR_NO_MEM CASO ascii_art SEJA nullptr
 * @return RETORNA ESP_FAIL CASO this->printf FALHE
*/
esp_err_t	Shell::wellcome_shell(void) {
	extern const uint8_t ascii_art_start[] asm("_binary_ascii_art_start");
	extern const uint8_t ascii_art_end[] asm("_binary_ascii_art_end");
	size_t len = ascii_art_end - ascii_art_start;
	char *ascii_art = new (std::nothrow) char[len + 1];
	if (ascii_art == nullptr) return (ESP_ERR_NO_MEM);
	memcpy(ascii_art, ascii_art_start, len);
	ascii_art[len] = '\0';
	int ret = this->printf(ascii_art);
	delete[] ascii_art;
	if (ret == -1) return (ESP_FAIL);
	return (ESP_OK);
}

/**
 * @author elguesabal
 * @brief METODO QUE SERA USADO COMO HANDLER PARA A TASK DE EXECUCAO DE COMANDOS DOS SHELL
 * @param arg ARGUMENTO PASSADO NA CRIACAO DA TASK (ESSE ARGUMENTO RECEBE this DA PROPRIA CLASSE)
*/
void	Shell::task_shell(void *arg) {
	Shell *shell = static_cast<Shell *>(arg);
	if (shell->wellcome_shell() != ESP_OK) shell->stop_task_shell();
	while (true) {
		if (WebServer::send_text_ws_fd(shell->port, shell->fd, "elguesabal@VampetaOS:~$ ", 24) != ESP_OK) break;
		char input[SHELL_INPUT_MAX];
		if (xQueueReceive(shell->queue, input, portMAX_DELAY) != pdPASS) {
			WebServer::send_text_ws_fd(shell->port, shell->fd, "ERROR INPUT\n", 12);
			break;
		}
		shell->run(input);
	}
	shell->stop_task_shell();
}

			void	print_command(const Command &command) {
				::printf("command.command ---> %s\n", command.command.c_str());
				::printf("command.args ---> { ");
				for (size_t i = 0; i < command.args.size(); i++) {
					::printf("%s", command.args[i].c_str());
					if (i + 1 < command.args.size()) ::printf(", ");
				}
				::printf(" }\n");
			}
/**
 * @author elguesabal
 * @brief METODO QUE RECEBE O INPUT E EXECUTA O COMANDO (METODO CHAMADO POR task_shell)
 * @param input COMANDO RECEBIDO PARA SER INTERPRETADO PELO SHELL
*/
void	Shell::run(std::string input) {
// INTERPRETAR O input E SEPARAR SEU COMANDO DOS ARGUMENTOS
	if (!this->parse_input(input)) {
		this->printf("ERROR INPUT\n");
		return;
	}
print_command(command);
// VERIFICAR SE JA ESTA LOGADO
	if (!this->check_authentication()) {
		this->printf("Access denied: no active user session.\nPlease authenticate using \"login\" or create an account using \"useradd\".\n");
		return;
	}
// EXECUTAR OS COMANDOS

if (this->command.command == "test") { // PQ NAO FUNCIONOU??? // ATA FUNCIONA COM O COMANDO login ANTES
this->fd_output = 1;
	this->printf("===== TEST ====\n");
	for (int i = 0; i < this->command.args.size(); i++) {
		std::string output = this->command.args[i] + " ";
		this->printf(output.c_str());
sleep(1);
	}
	this->printf("\n===== TEST ====\n");
this->fd_output = this->fd;
}
	if (this->command.command == "useradd") this->useradd();
	else if (this->command.command == "login") this->login();
	else if (this->command.command == "echo") this->echo();
	else if (this->command.command == "ls") this->printf("a.out VampetaOS.c\n");
	else if (this->command.command == "pwd") this->printf("/VampetaOS/\n");
	else this->printf("Command not found\n");
}

/**
 * @author elguesabal
 * @brief PARA A TASK DO SHELL
*/
void	Shell::stop_task_shell(void) {
	if (this->task != nullptr) {
		this->task = nullptr;
		vTaskDelete(NULL);
	}
}