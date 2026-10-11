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

// #include <sys/stat.h>
// #include <errno.h>
// #include <string.h>
// #include <stdio.h>

// #include <string>

#include "../VampetaOS.hpp"

#include "../Sd/Sd.hpp"
// #include "../System/System.hpp"

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WIFI
*/
class Wifi {
	private:
		static std::string	ssid;
		static std::string	password;

	public:
		// /Wifi/wifi.cpp
		static bool					init_wifi(void);

		// /Wifi/getters.cpp
		static const std::string	&get_ssid(void);
		static const std::string	&get_password(void);

		// /Wifi/setters.cpp
		static bool					set_ssid(const char *ssid);
		static bool					set_password(const char *password);

	private:
		// /Wifi/wifi.cpp
		static bool					init_dir(void);
};

#endif