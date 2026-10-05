/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/System.hpp                                                        |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include <string>

#include "../Sd/Sd.hpp"

#define MOUNT_POINT	"/sdcard"
#define DIR_SYSTEM	"/VampetaOS"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O SYSTEMA
*/
class System {
	public:
		static bool			init_system(void);
		static std::string	full_path(const char *path);

	private:
		static bool			init_dir(void);
};

#endif