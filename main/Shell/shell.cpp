/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/shell.cpp                                                          |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_shell                                                                |
  |  Shell                                                                     |
  |  ~Shell                                                                    |
  |  is_initialized                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief INICIA O SHELL
 * @return RETORNA true EM CASO DO SHELL INICIADO COM SUCESSO
 * @return RETORNA false CASO check_dir FALHE
*/
bool	Shell::init_shell(void) {
	if (!Shell::check_dir()) return (false);
	printf("Shell: OK\n");
	return (true);
}

/**
 * @author elguesabal
 * @brief CONSTRUTOR DA CLASSE Shell
 * @param connect STRUCT CONTENDO port E fd DA CONEXAO
*/
Shell::Shell(const WebSocket_connect &connect) : port(connect.port), fd(connect.fd), task(nullptr), queue(nullptr), logged_in(false), user(""), pwd(""), command() {
	this->queue = xQueueCreate(10, SHELL_INPUT_MAX);
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
	if (this->task != nullptr) {
		vTaskDelete(this->task);
		this->task = nullptr;
	}
	if (this->queue != nullptr) {
		vQueueDelete(this->queue);
		this->queue = nullptr;
	}
}

/**
 * @author elguesabal
 * @brief VERIFICA SE A TASK E O QUEUE FORAM CRIADOS CORRETAMENTE
 * @return RETORNA true EM CASO DA TASK E QUEUE INICIADOS COM SUCESSO
 * @return RETORNA false EM CASO DE FALHA NA CRIACAO DA TASK OU QUEUE
*/
bool	Shell::is_initialized(void) const {
	return (this->task != nullptr && this->queue != nullptr);
}