/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/setters.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  set_ssid                                                                  |
  |  set_password                                                              |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

/**
 * @author elguesabal
 * @brief SALVA A VARIAVEL ssid
 * @param ssid SSID QUE SERA SALVO
 * @return RETORNA true EM CASO DE SUCESSO
 * @return RETORNA false EM CASO DE ssid SER NULL
 * @return RETORNA false EM CASO DE ssid SER UMA STRING VAZIA
*/
bool	Wifi::set_ssid(const char *ssid) {
	if (ssid == NULL || ssid[0] == '\0') return (false);
	Wifi::ssid = ssid;
	return (true);
}

/**
 * @author elguesabal
 * @brief SALVA A VARIAVEL password
 * @param password PASSWORD QUE SERA SALVO
 * @return RETORNA true EM CASO DE SUCESSO
 * @return RETORNA false EM CASO DE password SER NULL
*/
bool	Wifi::set_password(const char *password) {
	if (password == NULL) return (false);
	Wifi::password = password;
	return (true);
}