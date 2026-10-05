/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /System/System.cpp                                                        |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_system                                                               |
  |  init_dir                                                                  |
  |  full_path                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "System.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA O SISTEMA
 * @return RETORNA true PARA ARQUIVOS DE SISTEMA OK
 * @return RETORNA false CASO init_dir FALHE
*/
bool	System::init_system(void) {
	if (!init_dir()) return (false);
	return (true);
}

/**
 * @author elguesabal
 * @brief INICIALIZA O SISTEMA
 * @return RETORNA true PARA ARQUIVOS DE SISTEMA OK
 * @return RETORNA false SE EXISTIR UM ARQUIVO COM O NOME /VampetaOS
 * @return RETORNA false SE O DIRETORIO DE SISTEMA NAO EXISTE A FALHE NA CRIACAO
*/
bool    System::init_dir(void) {
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

/**
 * @author elguesabal
 * @brief CRIA UMA STRING COM O PATH COMPLETO PARA SER USADO INTERNAMENTE (INCLUI NO PATH NOME DA UNIDADE E DIRETORIO DO SISTEMA)
 * @param path CAMINHO POSTERIOR DO NOME DA UNIDADE E DIRETORIO DO SISTEMA
 * @return RETORNA UMA STRING COM O PATH COMPLETO
*/
std::string	System::full_path(const char *path) {
	return (std::string(MOUNT_POINT) + DIR_SYSTEM + path);
}