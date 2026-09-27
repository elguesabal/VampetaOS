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
	esp_err_t ret;
	spi_bus_config_t bus_cfg = {};
	sdspi_device_config_t slot_config;
	sdmmc_host_t host;
	sdmmc_card_t *card;
	esp_vfs_fat_mount_config_t mount_config = {};

	bus_cfg.mosi_io_num = MOSI;
	bus_cfg.miso_io_num = MISO;
	bus_cfg.sclk_io_num = SCK;
	bus_cfg.quadwp_io_num = -1;
	bus_cfg.quadhd_io_num = -1;
	ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);
	if (ret != ESP_OK) {
		printf("Erro ao inicializar SPI\n");
		return (false);
	}
	slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
	slot_config.gpio_cs = CS;
	slot_config.host_id = SPI2_HOST;
	host = SDSPI_HOST_DEFAULT();
	host.slot = SPI2_HOST;
	mount_config.format_if_mount_failed = false;
	mount_config.max_files = 5;
	mount_config.allocation_unit_size = 16 * 1024;
	ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);
	if (ret != ESP_OK) {
		printf("Erro ao montar o SD: %s\n", esp_err_to_name(ret));
		return (false);
	}
	printf("Cartao SD montado\n");
	return (true);
}

/**
 * @author elguesabal
 * @brief LISTA OS DIRETORIOS NO path RECEBIDO
 * @param path CAMINHO RECEBIDO PARA CONSULTA
 * @return RETORNA UMA LISTA DO STRUCT DirectoryEntry CONTENDO OS NOMES E IDENTIFICANDO DIRETORIOS E ARQUIVOS
*/
std::vector<DirectoryEntry>	Sd::list_dir(const char *path) {
	DIR							*dir;
	struct dirent				*entry;
	std::vector<DirectoryEntry>	entries;

	dir = opendir(path);
	if (dir == NULL) {
		printf("Nao foi possivel abrir o diretorio\n");
		return (std::vector<DirectoryEntry>());
	}
	while ((entry = readdir(dir)) != NULL) {
		DirectoryEntry	item;
		item.name = entry->d_name;
		item.isDirectory = (entry->d_type == DT_DIR);
		entries.push_back(item);
	}
	closedir(dir);
	return (entries);
}