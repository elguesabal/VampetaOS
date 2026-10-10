/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Sd/directory.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  exist_dir                                                                 |
  |  create_dir                                                                |
  |  remove_dir                                                                |
  |  list_dir                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Sd.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE O DIRETORIO EXISTE
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA true CASO O DIRETORIO EXISTA
 * @return RETORNA false CASO O SEJA UM ARQUIVO
 * @return RETORNA false CASO NAO EXISTA
*/
bool	Sd::exist_dir(const char *path) {
	struct stat info;
	if (stat(System::full_path(path).c_str(), &info) != 0) return (false);
	return (S_ISDIR(info.st_mode));
}

/**
 * @author elguesabal
 * @brief CRIA UM DIRETORIO
 * @param path CAMINHO QUE DESEJA CRIAR O DIRETORIO
 * @return RETORNA true CASO O DIRETORIO SEJA CRIADO
 * @return RETORNA false EM CASO DE FALHA
*/
bool	Sd::create_dir(const char *path) {
	return (mkdir(System::full_path(path).c_str(), 0777) == 0);
}

/**
 * @author elguesabal
 * @brief REMOVE UM DIRETORIO
 * @param path CAMINHO DO DIRETORIO QUE DESEJA EXCLUIR
 * @return RETORNA true CASO O DIRETORIO SEJA EXCLUIDO
 * @return RETORNA false EM CASO DE FALHA
*/
bool	Sd::remove_dir(const char *path) {
	return (rmdir(System::full_path(path).c_str()) == 0);
}

/**
 * @author elguesabal
 * @brief REMOVE UM DIRETORIO E TUDO QUE OUVER DENTRO
 * @param path CAMINHO DO DIRETORIO QUE DESEJA EXCLUIR
 * @return RETORNA true CASO O DIRETORIO SEJA EXCLUIDO
 * @return RETORNA false CASO A O METODO list_dir GERE UM ERRO
 * @return RETORNA false CASO A O METODO delete_dir GERE UM ERRO
 * @return RETORNA false CASO A O METODO delete_file GERE UM ERRO
 * @return RETORNA false CASO A O METODO remove_dir GERE UM ERRO
*/
bool	Sd::delete_dir(const char *path) {
	std::vector<DirectoryEntry> entries = list_dir(path);
	if (errno != 0) return (false);
	for (size_t i = 0; i < entries.size(); i++) {
		std::string entry_path = std::string(path);
		if (!entry_path.empty() && entry_path[entry_path.size() - 1] != '/') entry_path += '/';
		entry_path += entries[i].name;
		if (entries[i].isDirectory) {
			if (!delete_dir(entry_path.c_str())) return (false);
		} else {
			if (!delete_file(entry_path.c_str())) return (false);
		}
	}
	return (remove_dir(path));
}

/**
 * @author elguesabal
 * @brief LISTA OS DIRETORIOS NO path RECEBIDO
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA UMA LISTA DO STRUCT DirectoryEntry CONTENDO OS NOMES E IDENTIFICANDO DIRETORIOS E ARQUIVOS EM CASO DE SUCESSO E SALVA 0 EM errno
 * @return RETORNA UMA LISTA DO STRUCT DirectoryEntry VAZIA EM CASO DE opendir GERAR UM ERRO
 * @return RETORNA UMA LISTA DO STRUCT DirectoryEntry VAZIA EM CASO DE readdir GERAR UM ERRO
*/
std::vector<DirectoryEntry>	Sd::list_dir(const char *path) {
	DIR *dir = opendir(System::full_path(path).c_str());
	if (dir == NULL) return (std::vector<DirectoryEntry>());
	struct dirent *entry;
	std::vector<DirectoryEntry> entries;
	errno = 0;
	while ((entry = readdir(dir)) != NULL) {
		DirectoryEntry	item;
		item.name = entry->d_name;
		item.isDirectory = (entry->d_type == DT_DIR);
		entries.push_back(item);
	}
	closedir(dir);
	if (errno != 0) return (std::vector<DirectoryEntry>());
	return (entries);
}