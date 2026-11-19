/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/shell.cpp                                                          |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_shell                                                                |
  |  Shell                                                                     |
  |  ~Shell                                                                    |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief INICIA O SHELL
 * @return RETORNA true EM CASO DO SHELL INICIADO COM SUCESSO
 * @return RETORNA false CASO ??? FALHE
*/
bool	Shell::init_shell(void) {
	if (!Shell::check_dir()) return (false);
	printf("Shell: OK\n");
	return (true);
}

/**
 * @author elguesabal
 * @brief CONSTRUTOR DA CLASSE Shell
 * @param port PORTA DA CONEXAO
 * @param fd FILE DESCRIPTION DA CONEAXO
*/
Shell::Shell(uint16_t port, int fd) : port(port), fd(fd), task(nullptr), queue(nullptr), logged_in(false), user(""), pwd(""), command() {
	this->queue = xQueueCreate(10, sizeof(std::string)); // EU DEVERIA USAR char* EM VEZ DE std::string
	if (this->queue == nullptr) return;
	if (xTaskCreate(this->task_shell, "Shell", 4096, this, 1, &this->task) != pdPASS) {
		vQueueDelete(this->queue);
		this->queue = nullptr;
	}
}

/**
 * @author elguesabal
 * @brief DESTRUTOR DA CLASSE Shell
*/
Shell::~Shell(void) {
	if (this->task == nullptr) return;
	vTaskDelete(this->task);
	this->task = nullptr;
	if (this->queue == nullptr) return;
	vQueueDelete(this->queue);
	this->queue = nullptr;
}