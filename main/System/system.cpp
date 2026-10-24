/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/system.cpp                                                        |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_system                                                               |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "System.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA O SISTEMA
 * @return RETORNA true PARA ARQUIVOS DE SISTEMA OK
 * @return RETORNA false CASO check_dir FALHE
 * @return RETORNA false CASO init_nvs_flash FALHE
*/
bool	System::init_system(void) {
	if (!System::check_dir()) return (false);
	if (!System::init_nvs_flash()) return (false);
	printf("System: OK\n");
	return (true);
}