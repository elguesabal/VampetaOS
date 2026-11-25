/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/commnads/useradd.cpp                                               |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  useradd                                                                   |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "../Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO RESPONSAVEL PELO COMANDO useradd
*/
void	Shell::useradd(void) {
	// this->emit_output("FINISHED", "\n");
WebServer::send_text_ws_fd(this->port, this->fd, "\n");
}