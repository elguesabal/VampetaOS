/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
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
 * @return RETORNA UMA STRING DE RESPOSTA
*/
std::string	Shell::echo(void) {
	// std::string ret;
	// for (int i = 0; i < this->command.args.size(); i++) ret += this->command.args[i] + " ";
	// ret += "\n";
	// return (ret);



	// for (int i = 0; i < this->command.args.size(); i++) {
	// 	std::string output = this->command.args[i] + " ";
	// 	WebServer::send_text_ws_fd(this->port, this->fd, output.c_str());
	// 	sleep(1);
	// }
	// WebServer::send_text_ws_fd(this->port, this->fd, "\n");



	for (int i = 0; i < this->command.args.size(); i++) {
		std::string output = this->command.args[i] + " ";
		this->emit_output("OUTPUT", output.c_str());
		sleep(1);
	}
	this->emit_output("FINISHED", "\n");
return ("");
}