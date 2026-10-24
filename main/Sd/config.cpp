/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Sd/config.cpp                                                            |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  get_config                                                                |
  |  set_config                                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Sd.hpp"

/**
 * @author elguesabal
 * @brief LE UMA CONFIGURACAO COM BASE NO path E name
 * @param path CAMINHO DO ARQUIVO DE CONFIGURACAO
 * @param name NOME DA CONFIGURACAO
 * @return RETORNA O VALOR DA CONFIGURACAO E SALVA 0 DENTRO DE errno CASO SUCESSO
 * @return RETORNA "" CASO A FUNCAO open GERE UM ERRO
 * @return RETORNA "" CASO A FUNCAO read GERE UM ERRO
 * @return RETORNA "" CASO A CONFIGURACAO ESTEJA INVALIDA E SALVA 0 DENTRO DE errno
 * @return RETORNA "" CASO A CONFIGURACAO NAO SEJA ENCONTRADA E SALVA 0 DENTRO DE errno
*/
std::string	Sd::get_config(const char *path, const char *name) {
	int fd = open(System::full_path(path).c_str(), O_RDONLY);
	if (fd == -1) return ("");
	char buffer[256];
	std::string content;
	ssize_t bytes;
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) content.append(buffer, bytes);
	close(fd);
	if (bytes == -1) return ("");
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
				if (first_quote == std::string::npos || last_quote == std::string::npos || first_quote == last_quote) {
					errno = 0;
					return ("");
				}
				errno = 0;
				return (line.substr(first_quote + 1, last_quote - first_quote - 1));
			}
		}
		if (end == content.size()) break;
		pos = end + 1;
	}
	errno = 0;
	return ("");
}

/**
 * @author elguesabal
 * @brief ATUALIZA OU INSERE UMA CONFIGURACAO NO ARQUIVO COM BASE NO path E name
 * @param path CAMINHO DO ARQUIVO DE CONFIGURACAO
 * @param name NOME DA CONFIGURACAO
 * @param value NOVO VALOR DA CONFIGURACAO
 * @return RETORNA true CASO A CONFIGURACAO SEJA SALVA COM SUCESSO
 * @return RETORNA false CASO A FUNCAO open GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO read GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO open GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO read GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO close GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO unlink GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO rename GERE UM ERRO
 * @return RETORNA false CASO A FUNCAO rename GERE UM ERRO
 * @return RETORNA false CASO A QUANTIDADE DE BYTES ESCRITOS SEJA DIFERENTE DO PEDIDO
*/
bool Sd::set_config(const char *path, const char *name, const char *value) {
	std::string full_path = System::full_path(path);
	std::string temp_path = full_path + ".tmp";
	std::string backup_path = full_path + ".bak";
	int fd = open(full_path.c_str(), O_RDONLY);
	if (fd == -1) return (false);
	char buffer[256];
	std::string content;
	ssize_t bytes;
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) content.append(buffer, bytes);
	close(fd);
	if (bytes == -1) return (false);
	size_t pos = 0;
	bool found = false;
	while (pos < content.size()) {
		size_t end = content.find('\n', pos);
		if (end == std::string::npos) end = content.size();
		std::string line = content.substr(pos, end - pos);
		size_t equal = line.find('=');
		if (equal != std::string::npos) {
			std::string current_name = line.substr(0, equal);
			if (current_name == name) {
				std::string new_line = std::string(name) + "=\"" + value + "\"";
				content.replace(pos, end - pos, new_line);
				found = true;
				break;
			}
		}
		if (end == content.size()) break;
		pos = end + 1;
	}
	if (!found) {
		if (!content.empty() && content[content.size() - 1] != '\n') content += '\n';
		content += std::string(name) + "=\"" + value + "\"\n";
	}
	fd = open(temp_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1) return (false);
	size_t written = 0;
	while (written < content.size()) {
		bytes = write(fd, content.c_str() + written, content.size() - written);
		if (bytes <= 0) {
			int error = (bytes == -1) ? errno : EIO;
			close(fd);
			unlink(temp_path.c_str());
			errno = error;
			return (false);
		}
		written += bytes;
	}
	if (close(fd) == -1) {
		int error = errno;
		unlink(temp_path.c_str());
		errno = error;
		return (false);
	}
	if (unlink(backup_path.c_str()) == -1 && errno != ENOENT) {
		int error = errno;
		unlink(temp_path.c_str());
		errno = error;
		return (false);
	}
	if (rename(full_path.c_str(), backup_path.c_str()) == -1) {
		int error = errno;
		unlink(temp_path.c_str());
		errno = error;
		return (false);
	}
	if (rename(temp_path.c_str(), full_path.c_str()) == -1) {
		int error = errno;
		if (rename(backup_path.c_str(), full_path.c_str()) == -1) {
			errno = error;
			return (false);
		}
		unlink(temp_path.c_str());
		errno = error;
		return (false);
	}
	unlink(backup_path.c_str());
	errno = 0;
	return (true);
}