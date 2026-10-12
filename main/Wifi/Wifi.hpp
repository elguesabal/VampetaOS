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

#include "../VampetaOS.hpp"
#include "../Sd/Sd.hpp"



#include <string.h>
#include <stdio.h>

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"



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
static bool	connect(void);

		// /Wifi/getters.cpp
		static const std::string	&get_ssid(void);
		static const std::string	&get_password(void);

		// /Wifi/setters.cpp
		static bool					set_ssid(const char *ssid);
		static bool					set_password(const char *password);

	private:
		// /Wifi/wifi.cpp
		static bool					init_dir(void);
static void					wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
};

#endif