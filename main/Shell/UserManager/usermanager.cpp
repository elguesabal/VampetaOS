/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /UserManager/usermanager.cpp                                             |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "UserManager.hpp"

UserManager::UserManager(void) : logged_in(false), user("") {

}

UserManager::~UserManager(void) {

}

bool	UserManager::get_logeed_in(void) {
	return (this->logged_in);
}

std::string	UserManager::get_user(void) {
	return (this->user);
}

/**
 * @author elguesabal
 * @brief 
 * @param command STRUCT QUE ARMAZENA O NOME DO COMANDO E SEUS ARGUMENTOS
 * @return RETORNA true 
 * @return RETORNA false 
*/
bool	UserManager::user_manager(const Command &command) {
	(void)command;
	return (true);
}