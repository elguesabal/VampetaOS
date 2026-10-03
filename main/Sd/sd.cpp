/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Sd/Sd.cpp                                                                |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_sd                                                                   |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Sd.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA O CARTAO SD
 * @return RETORNA true PARA INICIALIZACAO CORRETA DO CARTAO SD
 * @return RETORNA false PARA ERRO NA INICIALIZACAO DO CARTAO SD
*/
bool	Sd::init_sd(void) {
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
		spi_bus_free(SPI2_HOST);
		return (false);
	}
	printf("SD card: OK\n");
	return (true);
}