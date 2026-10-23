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

#define WIFI_CONNECTED_BIT	BIT0
#define WIFI_FAIL_BIT		BIT1
#define WIFI_MAX_RETRIES	5

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O WIFI
*/
class Wifi {
	private:
		// /Wifi/wifi.cpp
		static EventGroupHandle_t	wifi_event_group;
		static int					retry_count;
		static std::string			ssid;
		static std::string			password;

	public:
		// /Wifi/wifi.cpp
		static bool					init_wifi(void);

		// /Wifi/getters.cpp
		static const std::string	&get_ssid(void);
		static const std::string	&get_password(void);

		// /Wifi/setters.cpp
		static bool					set_ssid(const char *ssid);
		static bool					set_password(const char *password);

		// /Wifi/connect.cpp
		// static bool	connect(const char *ssid, const char *password);
		static std::string			ip(void);

	private:
		// /Wifi/directory.cpp
		static bool					check_dir(void);

		// /Wifi/connect.cpp
		static bool	init(void);
		static void	wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
		static bool	register_events(void);
		static bool	connect(void);
};

#endif