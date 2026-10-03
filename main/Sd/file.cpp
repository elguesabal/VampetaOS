/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Sd/file.cpp                                                              |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  exist_file                                                                |
  |  create_file                                                               |
  |  create_file                                                               |
  |  write_file                                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Sd.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE O ARQUIVO EXISTE
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA true CASO O ARQUIVO EXISTA
 * @return RETORNA false CASO O SEJA UM DIRETORIO
 * @return RETORNA false CASO NAO EXISTA
*/
bool	Sd::exist_file(const char *path) {
	struct stat info;
	if (stat(System::full_path(path).c_str(), &info) != 0) return (false);
	return (S_ISREG(info.st_mode));
}

/**
 * @author elguesabal
 * @brief CRIA UM ARQUIVO VAZIO
 * @param path CAMINHO QUE DESEJA CRIAR O ARQUIVO
 * @return RETORNA true CASO O ARQUIVO SEJA CRIADO
 * @return RETORNA false CASO JA EXISTA ALGO COM MESMO NOME
 * @return RETORNA false CASO O ARQUIVO NAO SEJA CRIADO
*/
bool	Sd::create_file(const char *path) {
	int fd = open(System::full_path(path).c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd == -1) return (false);
	close(fd);
	return (true);
}

/**
 * @author elguesabal
 * @brief CRIA UM ARQUIVO VAZIO E ADICIONA VALOR
 * @param path CAMINHO QUE DESEJA CRIAR O ARQUIVO
 * @param content VALOR QUE VAI SER ADICIONADO AO ARQUIVO
 * @return RETORNA true CASO O ARQUIVO SEJA CRIADO
 * @return RETORNA false CASO JA EXISTA ALGO COM MESMO NOME
 * @return RETORNA false CASO O ARQUIVO NAO SEJA CRIADO
 * @return RETORNA false CASO A FUNCAO WRITE ESCREVA MENOS BYTES DO ENVIADO
*/
bool	Sd::create_file(const char *path, const char *content) {
	if (content == NULL) return (false);
	int fd = open(System::full_path(path).c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd == -1) return (false);
	ssize_t bytes = write(fd, content, strlen(content));
	if (bytes != (ssize_t)strlen(content)) {
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

// /**
//  * @author elguesabal
//  * @brief ADICIONA VALOR NO INICIO DO ARQUIVO
//  * @param path CAMINHO QUE DESEJA CRIAR O ARQUIVO
//  * @param content VALOR QUE VAI SER ADICIONADO AO ARQUIVO
//  * @return RETORNA true CASO O ARQUIVO SEJA ESCRITO
//  * @return RETORNA false CASO A FUNCAO WRITE ESCREVA MENOS BYTES DO ENVIADO
//  * @return RETORNA false CASO O ARQUIVO NAO EXISTA
// */
// bool	Sd::write_file(const char *path, const char *content) {
//	if (content == NULL) return (false);
// 	int fd = open(System::full_path(path).c_str(), O_WRONLY);
// 	if (fd == -1) return (false);
// 	ssize_t bytes = write(fd, content, strlen(content));
// 	if (bytes != (ssize_t)strlen(content)) {
// 		close(fd);
// 		return (false);
// 	}
// 	close(fd);
// 	return (true);
// }