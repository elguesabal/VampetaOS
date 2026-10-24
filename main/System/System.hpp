/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/System.hpp                                                        |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "../VampetaOS.hpp"
#include "../Sd/Sd.hpp"

#define MOUNT_POINT	"/sdcard"
#define DIR_SYSTEM	"/VampetaOS"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O SYSTEMA
*/
class System {
	public:
		// /System/system.cpp
		static bool			init_system(void);

		// /System/flash.cpp
		static bool			init_nvs_flash(void);

		// /System/path.cpp
		static std::string	full_path(const char *path);

	private:
		// /System/directory.cpp
		static bool			check_dir(void);
};

#endif