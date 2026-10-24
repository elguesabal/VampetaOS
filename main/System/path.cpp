/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/path.cpp                                                          |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  full_path                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "System.hpp"

/**
 * @author elguesabal
 * @brief CRIA UMA STRING COM O PATH COMPLETO PARA SER USADO INTERNAMENTE (INCLUI NO PATH NOME DA UNIDADE E DIRETORIO DO SISTEMA)
 * @param path CAMINHO POSTERIOR DO NOME DA UNIDADE E DIRETORIO DO SISTEMA
 * @return RETORNA UMA STRING COM O PATH COMPLETO
*/
std::string	System::full_path(const char *path) {
	return (std::string(MOUNT_POINT) + DIR_SYSTEM + path);
}