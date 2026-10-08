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
	if (stat(System::full_path(path).c_str(), &info) == -1) return (false);
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
}

/**
 * @author elguesabal
 * @brief LE UMA CONFIGURACAO COM BASE NO path E name
 * @param path CAMINHO DO ARQUIVO DE CONFIGURACAO
 * @param name NOME DA CONFIGURACAO
 * @param value REFERENCIA QUE VAI ARMAZENAR O VALOR DA CONFIGURACAO
 * @return RETORNA true CASO A CONFIGURACAO SEJA LIDA E ARMAZENADA EM value COM SUCESSO E SALVA 0 DENTRO DE errno
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO read RETORNE GERE UM ERRO
 * @return RETORNA false CASO A CONFIGURACAO ESTEJA INVALIDA
 * @return RETORNA false CASO A CONFIGURACAO NAO SEJA ENCONTRADA
*/
bool	Sd::get_config(const char *path, const char *name, std::string &value) {
	int fd = open(System::full_path(path).c_str(), O_RDONLY);
	if (fd == -1) return (false);
	char buffer[256];
	std::string content;
	ssize_t bytes;
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) content.append(buffer, bytes);
	close(fd);
	if (bytes == -1) return (false);
	size_t pos = 0;
	while (pos < content.size()) {
		size_t end = content.find('\n', pos);
		if (end == std::string::npos) end = content.size();
		std::string line = content.substr(pos, end - pos);
		size_t equal = line.find('=');
		if (equal != std::string::npos) {
			std::string current_name = line.substr(0, equal);
			if (current_name == name) {
				size_t first_quote = line.find('"', equal);
				size_t last_quote = line.rfind('"');
				if (first_quote == std::string::npos || last_quote == std::string::npos || first_quote == last_quote) return (false);
				value = line.substr(first_quote + 1, last_quote - first_quote - 1);
				return (true);
			}
		}
		if (end == content.size()) break;
		pos = end + 1;
	}
	errno = 0;
	return (false);
}

/**
 * @author elguesabal
 * @brief ESCREVE UMA CONFIGURACAO COM BASE NO path E name
 * @param path CAMINHO DO ARQUIVO DE CONFIGURACAO
 * @param name NOME DA CONFIGURACAO
 * @param value REFERENCIA QUE VAI ARMAZENAR O VALOR DA CONFIGURACAO
 * @return RETORNA true CASO A CONFIGURACAO SEJA SALVA COM SUCESSO
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO read RETORNE GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO open RETORNE GERE UM ERRO
 * @return RETORNA false CASO A QUANTIDADE DE BYTES ESCRITOS SEJA DIFERENTE DO PEDIDO
*/
bool	Sd::set_config(const char *path, const char *name, const char *value) {
	int fd = open(System::full_path(path).c_str(), O_RDONLY);
	if (fd == -1) return (false);
	char buffer[256];
	std::string content;
	ssize_t bytes;
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) content.append(buffer, bytes);
	close(fd);
	if (bytes == -1) return (false);
	size_t pos = 0;
	while (pos < content.size()) {
		size_t end = content.find('\n', pos);
		if (end == std::string::npos) end = content.size();
		std::string line = content.substr(pos, end - pos);
		size_t equal = line.find('=');
		if (equal != std::string::npos) {
			std::string current_name = line.substr(0, equal);
			if (current_name == name) {
				std::string new_line;
				new_line = std::string(name) + "=\"" + value + "\"";
				content.replace(pos, end - pos, new_line);
				break;
			}
		}
		if (end == content.size()) break;
		pos = end + 1;
	}
	fd = open(System::full_path(path).c_str(), O_WRONLY | O_TRUNC);
	if (fd == -1) return (false);
	bytes = write(fd, content.c_str(), content.size());
	close(fd);
	return (bytes == (ssize_t)content.size());
}