/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/directory.cpp                                                     |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  check_dir                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "System.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA O SISTEMA
 * @return RETORNA true PARA ARQUIVOS DE SISTEMA OK
 * @return RETORNA false SE EXISTIR UM ARQUIVO COM O NOME /VampetaOS
 * @return RETORNA false SE O DIRETORIO DE SISTEMA NAO EXISTE A FALHE NA CRIACAO
*/
bool	System::check_dir(void) {
	if (Sd::exist_dir("/")) {
		printf("System: OK\n");
		return (true);
	}
	if (Sd::exist_file("/")) {
		printf("%s must be a directory\n", DIR_SYSTEM);
		return (false);
	}
	if (!Sd::create_dir("/")) {
		printf("%s\n", strerror(errno));
		return (false);
	}
	printf("System: OK\n");
	return (true);
}