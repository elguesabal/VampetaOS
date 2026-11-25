/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/commnads/echo.cpp                                                  |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  echo                                                                      |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "../Shell.hpp"

/**
 * @author elguesabal
 * @brief METODO RESPONSAVEL PELO COMANDO echo
*/
void	Shell::echo(void) {
	for (int i = 0; i < this->command.args.size(); i++) {
		std::string output = this->command.args[i] + " ";
		// this->emit_output("OUTPUT", output.c_str());
// WebServer::send_text_ws_fd(this->port, this->fd, output.c_str());
this->write(this->fd, output.c_str(), output.size());
sleep(1);
	}
	// this->emit_output("FINISHED", "\n");
WebServer::send_text_ws_fd(this->port, this->fd, "\n");
}