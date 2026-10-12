/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/flash.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_nvs_flash                                                            |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "System.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA O SISTEMA NVS NA MEMORIA FLASH
 * @return RETORNA true PARA INICIALIZACAO COM SUCESSO
 * @return RETORNA false CASO nvs_flash_init FALHE
*/
bool	System::init_nvs_flash(void) {
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ret = nvs_flash_erase();
		if (ret == ESP_OK) ret = nvs_flash_init();
	}
	if (ret != ESP_OK) {
		printf("NVS initialization failed: %s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}