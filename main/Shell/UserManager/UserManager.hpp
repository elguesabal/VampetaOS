/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /UserManager/UserManager.hpp                                              |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "../../VampetaOS.hpp"
#include "../Command.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O CRIACAO DE USER E LOGIN
*/
class UserManager {
	private:
		bool		logged_in;
		std::string	user;

	public:
		// /UserManager/usermanager.cpp
		UserManager(void);
		~UserManager(void);
		bool		get_logeed_in(void);
		std::string	get_user(void);
		bool		user_manager(const Command &command);

};

#endif