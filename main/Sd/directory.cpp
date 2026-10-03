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
 * @param path CAMINHO QUE DESEJA EXCLUIR O DIRETORIO
 * @return RETORNA true CASO O DIRETORIO SEJA EXCLUIDO
 * @return RETORNA false EM CASO DE FALHA
*/
bool	Sd::remove_dir(const char *path) {
	return (rmdir(System::full_path(path).c_str()) == 0);
}

/**
 * @author elguesabal
 * @brief LISTA OS DIRETORIOS NO path RECEBIDO
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA UMA LISTA DO STRUCT DirectoryEntry CONTENDO OS NOMES E IDENTIFICANDO DIRETORIOS E ARQUIVOS
*/
std::vector<DirectoryEntry>	Sd::list_dir(const char *path) {		// AINDA SEM TRATAMENTO DE ERRO CORRETO
	DIR *dir = opendir(System::full_path(path).c_str());
	if (dir == NULL) {
		printf("Nao foi possivel abrir o diretorio\n");
		return (std::vector<DirectoryEntry>());
	}
	struct dirent *entry;
	std::vector<DirectoryEntry> entries;
	while ((entry = readdir(dir)) != NULL) {
		DirectoryEntry	item;
		item.name = entry->d_name;
		item.isDirectory = (entry->d_type == DT_DIR);
		entries.push_back(item);
	}
	closedir(dir);
	return (entries);
}