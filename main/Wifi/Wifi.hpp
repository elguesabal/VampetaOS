/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/Wifi.hpp                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef WIFI_H
#define WIFI_H

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <string>

#include "../Sd/Sd.hpp"
#include "../System/System.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WIFI
*/
class Wifi {
	public:
		static bool	init_wifi(void);

	private:
		static bool	init_dir(void);
};

#endif