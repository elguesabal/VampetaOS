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
  |  size_file                                                                 |
  |  create_file                                                               |
  |  create_file                                                               |
  |  write_file_truncate                                                       |
  |  write_file_append                                                         |
  |  read_file                                                                 |
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
 * @brief CONSULTA O TAMANHO DO ARQUIVO
 * @param path CAMINHO QUE DESEJA DO ARQUIVO
 * @return RETORNA UM VALOR POSITIVO COM O TAMANHO EM BYTES
 * @return RETORNA -1 CASO A FUNCAO stat RETORNE GERE UM ERRO
 * @return RETORNA -1 CASO path NAO APONTE PARA UM ARQUIVO
*/
off_t	Sd::size_file(const char *path) {
	struct stat info;
	if (stat(System::full_path(path).c_str(), &info) == -1) return (-1);
	if (!S_ISREG(info.st_mode)) return (-1);
	return (info.st_size);
}

/**
 * @author elguesabal
 * @brief CRIA UM ARQUIVO VAZIO
 * @param path CAMINHO QUE DESEJA CRIAR O ARQUIVO
 * @return RETORNA true CASO O ARQUIVO SEJA CRIADO
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
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
 * @return RETORNA false CASO O ARGUMENTO content SEJA NULL
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write ESCREVA MENOS BYTES DO ENVIADO
*/
bool	Sd::create_file(const char *path, const char *content) {
	if (content == NULL) {
		errno = EINVAL;
		return (false);
	}
	int fd = open(System::full_path(path).c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd == -1) return (false);
	size_t size = strlen(content);
	ssize_t bytes = write(fd, content, size);
	if (bytes == -1) {
		close(fd);
		return (false);
	}
	if ((size_t)bytes != size) {
		close(fd);
		errno = EIO;
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @author elguesabal
 * @brief SOBRESCREVE TODO O CONTEUDO DO ARQUIVO COM O VALOR INFORMADO
 * @param path CAMINHO QUE DESEJA ESCREVER NO ARQUIVO
 * @param content VALOR QUE VAI SER ESCRITO NO ARQUIVO
 * @return RETORNA true CASO O ARQUIVO SEJA ESCRITO CORRETAMENTE
 * @return RETORNA false CASO O ARGUMENTO content SEJA NULL
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write ESCREVA MENOS BYTES DO ENVIADO
*/
bool	Sd::write_file_truncate(const char *path, const char *content) {
	if (content == NULL) {
		errno = EINVAL;
		return (false);
	}
	int fd = open(System::full_path(path).c_str(), O_WRONLY | O_TRUNC);
	if (fd == -1) return (false);
	size_t size = strlen(content);
	ssize_t bytes = write(fd, content, size);
	if (bytes == -1) {
		close(fd);
		return (false);
	}
	if ((size_t)bytes != size) {
		close(fd);
		errno = EIO;
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @author elguesabal
 * @brief ESCREVE AO FINAL DO ARQUIVO
 * @param path CAMINHO QUE DESEJA ESCREVER NO ARQUIVO
 * @param content VALOR QUE VAI SER ADICIONADO AO FINAL DO ARQUIVO
 * @return RETORNA true CASO O ARQUIVO SEJA ESCRITO CORRETAMENTE
 * @return RETORNA false CASO O ARGUMENTO content SEJA NULL
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write ESCREVA MENOS BYTES DO ENVIADO
*/
bool	Sd::write_file_append(const char *path, const char *content) {
	if (content == NULL) {
		errno = EINVAL;
		return (false);
	}
	int fd = open(System::full_path(path).c_str(), O_WRONLY | O_APPEND);
	if (fd == -1) return (false);
	size_t size = strlen(content);
	ssize_t bytes = write(fd, content, size);
	if (bytes == -1) {
		close(fd);
		return (false);
	}
	if ((size_t)bytes != size) {
		close(fd);
		errno = EIO;
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @author elguesabal
 * @brief ESCREVE AO FINAL DO ARQUIVO
 * @param path CAMINHO QUE DESEJA LER O ARQUIVO
 * @param content REFERENCIA QUE VAI ARMAZENAR O CONTEUDO DO ARQUIVO
 * @return RETORNA true CASO O ARQUIVO SEJA LIDO CORRETAMENTE
 * @return RETORNA false CASO O ARGUMENTO content SEJA NULL
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO write ESCREVA MENOS BYTES DO ENVIADO
*/
bool	Sd::read_file(const char *path, std::string &content) {
	int fd = open(System::full_path(path).c_str(), O_RDONLY);
	if (fd == -1) return (false);
	char buffer[128];
	ssize_t bytes;
	content.clear();
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) content.append(buffer, bytes);
	close(fd);
	if (bytes == -1) return (false);
	return (true);

	// std::string full_path = System::full_path(path);
	// struct stat info;
	// if (stat(System::full_path(path).c_str(), &info) == -1) return (false);
	// if (!S_ISREG(info.st_mode)) return (false);
	// int fd = open(full_path.c_str(), O_RDONLY);
	// if (fd == -1) return (false);
	// content.resize(info.st_size);
	// ssize_t bytes = read(fd, content.data(), info.st_size);
	// close(fd);
	// if (bytes != info.st_size) {
	// 	content.clear();
	// 	return (false);
	// }
	// return (true);
}