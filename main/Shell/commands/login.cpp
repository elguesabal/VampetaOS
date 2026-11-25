/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/commnads/login.cpp                                                 |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  login                                                                     |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "../Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO RESPONSAVEL PELO COMANDO login
*/
void	Shell::login(void) {
	this->logged_in = true;
	// this->emit_output("FINISHED", "OK\n");
WebServer::send_text_ws_fd(this->port, this->fd, "OK\n");
}