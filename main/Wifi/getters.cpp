/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/getters.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  get_ssid                                                                  |
  |  get_password                                                              |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

/**
 * @author elguesabal
 * @brief BUSCA A VARIAVEL ssid
 * @return RETORNA ssid
*/
const std::string	&Wifi::get_ssid(void) {
	return (Wifi::ssid);
}

/**
 * @author elguesabal
 * @brief BUSCA A VARIAVEL password
 * @return RETORNA password
*/
const std::string	&Wifi::get_password(void) {
	return (Wifi::password);
}