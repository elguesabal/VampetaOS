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
  + -------------------------------------------------------------------------- +
*/

#include "WebShell.hpp"

std::string WebShell::shell(std::string command) {
	if (command == "ls") return ("a.out VampetaOS.c");
	if (command == "pwd") return ("/VampetaOS/");
	if (command == "echo VampetaOS") return ("VampetaOS");
	return ("Command not found");
}