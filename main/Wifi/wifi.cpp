/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/wifi.cpp                                                            |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_wifi                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

EventGroupHandle_t	Wifi::wifi_event_group;
int					Wifi::retry_count = 0;
std::string			Wifi::ssid = "";
std::string			Wifi::password = "";

/**
 * @author elguesabal
 * @brief INICIA O WIFI
 * @return RETORNA true EM CASO DE WIFI INICIADO COM SUCESSO
 * @return RETORNA false CASO check_dir FALHE
*/
bool	Wifi::init_wifi(void) {
	if (!Wifi::check_dir()) return (false);
	if (!Wifi::init()) return (false);
	if (!Wifi::register_events()) return (false);
	if (!Wifi::connect()) return (false);
	return (true);
}