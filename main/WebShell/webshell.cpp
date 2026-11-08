/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /WebShell/webshell.cpp                                                    |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |                                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "WebShell.hpp"

std::string WebShell::shell(std::string command) {
	if (command == "ls") return ("a.out VampetaOS.c\n");
	if (command == "pwd") return ("/VampetaOS/\n");
	if (command == "echo VampetaOS") return ("VampetaOS\n");
	return ("Command not found\n");
}




// WebShell::WebShell() {

// }

// void  run_command(void) {

// }