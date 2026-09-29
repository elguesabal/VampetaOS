/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /sd/sd.cpp                                                                |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  sd_init                                                                   |
  |  list_dir                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "sd.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA O CARTAO SD
 * @return RETORNA true PARA INICIALIZACAO CORRETA DO CARTAO SD
 * @return RETORNA false PARA ERRO NA INICIALIZACAO DO CARTAO SD
*/
bool	Sd::sd_init(void) {
	spi_bus_config_t bus_cfg = {};
	bus_cfg.mosi_io_num = MOSI;
	bus_cfg.miso_io_num = MISO;
	bus_cfg.sclk_io_num = SCK;
	bus_cfg.quadwp_io_num = -1;
	bus_cfg.quadhd_io_num = -1;
	esp_err_t ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
	slot_config.gpio_cs = CS;
	slot_config.host_id = SPI2_HOST;
	sdmmc_host_t host = SDSPI_HOST_DEFAULT();
	host.slot = SPI2_HOST;
	esp_vfs_fat_mount_config_t mount_config = {};
	mount_config.format_if_mount_failed = false;
	mount_config.max_files = 5;
	mount_config.allocation_unit_size = 16 * 1024;
	sdmmc_card_t *card;
	ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	printf("SD card mounted\n");
	return (true);
}

// Sd::init_dir()
// Sd::init_system()

/**
 * @author elguesabal
 * @brief VERIFICA SE O DIRETORIO EXISTE
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA true CASO O DIRETORIO EXISTA
 * @return RETORNA false CASO O SEJA UM ARQUIVO OU NAO EXISTA
*/
bool	Sd::exist_dir(const char *path) {
	struct stat info;
	if (stat(full_path(path).c_str(), &info) != 0) return (false);
	return (S_ISDIR(info.st_mode));
}

/**
 * @author elguesabal
 * @brief VERIFICA SE O ARQUIVO EXISTE
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA true CASO O ARQUIVO EXISTA
 * @return RETORNA false CASO O SEJA UM DIRETORIO OU NAO EXISTA
*/
bool	Sd::exist_file(const char *path) {
	struct stat info;
	if (stat(full_path(path).c_str(), &info) != 0) return (false);
	return (S_ISREG(info.st_mode));
}

/**
 * @author elguesabal
 * @brief CRIA UM DIRETORIO
 * @param path CAMINHO QUE DESEJA CRIAR O DIRETORIO
 * @return RETORNA true CASO O DIRETORIO SEJA CRIADO
 * @return RETORNA false CASO O DIRETORIO NAO SEJA CRIADO OU JA EXISTA ALGO COM MESMO NOME
*/
bool	Sd::create_dir(const char *path) {
	return (mkdir(full_path(path).c_str(), 0777) == 0);
}

/**
 * @author elguesabal
 * @brief REMOVE UM DIRETORIO
 * @param path CAMINHO QUE DESEJA EXCLUIR O DIRETORIO
 * @return RETORNA true CASO O DIRETORIO SEJA EXCLUIDO
 * @return RETORNA false CASO O DIRETORIO NAO SEJA EXCLUIDO
*/
bool	Sd::remove_dir(const char *path) {
	return (rmdir(full_path(path).c_str()) == 0);
}

/**
 * @author elguesabal
 * @brief REMOVE UM DIRETORIO
 * @param path CAMINHO QUE DESEJA EXCLUIR O DIRETORIO
 * @return RETORNA true CASO O ARQUIVO SEJA CRIADO
 * @return RETORNA false CASO O ARQUIVO NAO SEJA CRIADO OU JA EXISTA ALGO COM MESMO NOME
*/
bool	Sd::create_file(const char *path) {
	int fd = open(full_path(path).c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd == -1) return (false);
	close(fd);
	return (true);
}

// bool	Sd::create_file(const char *path, const char *value) {

// }

/**
 * @author elguesabal
 * @brief LISTA OS DIRETORIOS NO path RECEBIDO
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA UMA LISTA DO STRUCT DirectoryEntry CONTENDO OS NOMES E IDENTIFICANDO DIRETORIOS E ARQUIVOS
*/
std::vector<DirectoryEntry>	Sd::list_dir(const char *path) {		// AINDA SEM TRATAMENTO DE ERRO CORRETO
	DIR *dir = opendir(full_path(path).c_str());
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

/**
 * @author elguesabal
 * @brief CRIA UMA STRING COM O PATH COMPLETO PARA SER USADO INTERNAMENTE (INCLUI NO PATH NOME DA UNIDADE E DIRETORIO DO SISTEMA)
 * @param path CAMINHO POSTERIOR DO NOME DA UNIDADE E DIRETORIO DO SISTEMA
 * @return RETORNA UMA STRING COM O PATH COMPLETO
*/
std::string	Sd::full_path(const char *path) {
	return (std::string(MOUNT_POINT) + DIR_SYSTEM + path);
}