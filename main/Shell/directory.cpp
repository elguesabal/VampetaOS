/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Shell/directory.cpp                                                      |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  check_dir                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Shell.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE O ARQUIVO DE CONFIGURACAO DO SHELL EXISTE E CRIA CASO NAO
 * @return RETORNA true CASO /VampetaOS/shell/ENVIRONMENT EXISTA
 * @return RETORNA false CASO /VampetaOS/shell SEJA UM ARQUIVO
 * @return RETORNA false CASO /VampetaOS/shell NAO EXISTA E FALHE NA CRIACAO
 * @return RETORNA false CASO /VampetaOS/shell/ENVIRONMENT SEJA UM DIRETORIO
 * @return RETORNA false CASO /VampetaOS/shell/ENVIRONMENT NAO EXISTA E FALHE NA CRIACAO
 * @return RETORNA false CASO /VampetaOS/home SEJA UM ARQUIVO
 * @return RETORNA false CASO /VampetaOS/home NAO EXISTA E FALHE NA CRIACAO
*/
bool	Shell::check_dir(void) {
	if (!Sd::exist_dir("/shell")) {
		if (Sd::exist_file("/shell")) {
			printf("/VampetaOS/shell must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/shell")) {
			printf("Failed to create /VampetaOS/shell: %s\n", strerror(errno));
			return (false);
		}
	}
	if (Sd::exist_file("/shell/ENVIRONMENT")) {
// AKI EU PEGO AS VARIAVEIS DE AMBIENTE PRE CONFIGURADA ???
		return (true);
	}
	if (Sd::exist_dir("/shell/ENVIRONMENT")) {
		printf("/shell/ENVIRONMENT must be a file\n");
		return (false);
	}
	if (!Sd::create_file("/shell/ENVIRONMENT", "WIFI=\"\"\nPASSWORD=\"\"")) {
		printf("Failed to create /shell/ENVIRONMENT: %s\n", strerror(errno));
		return (false);
	}
if (!Sd::exist_dir("/home")) { // DEVERIA CRIAR O DIRETORIO home ???
	if (Sd::exist_file("/home")) {
		printf("/VampetaOS/home must be a directory\n");
		return (false);
	}
	if (!Sd::create_dir("/home")) {
		printf("Failed to create /VampetaOS/home: %s\n", strerror(errno));
		return (false);
	}
}
	return (true);
}