#include <stdio.h>
#include <dirent.h>

#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"

#define MOUNT_POINT "/sdcard"

void	app_main(void)
{
    esp_err_t ret;

    /*
     * Configuração do barramento SPI.
     *
     * IMPORTANTE:
     * Os GPIOs precisam ser os GPIOs usados pelo
     * microSD do seu Cardputer.
     */
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = GPIO_NUM_14,
        .miso_io_num = GPIO_NUM_39,
        .sclk_io_num = GPIO_NUM_40,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    ret = spi_bus_initialize(
        SPI2_HOST,
        &bus_cfg,
        SDSPI_DEFAULT_DMA
    );

    if (ret != ESP_OK)
    {
        printf("Erro ao inicializar SPI\n");
        return;
    }

    /*
     * Configuração do dispositivo SD.
     */
    sdspi_device_config_t slot_config =
        SDSPI_DEVICE_CONFIG_DEFAULT();

    slot_config.gpio_cs = GPIO_NUM_12;
    slot_config.host_id = SPI2_HOST;

    /*
     * Configuração do host SD.
     */
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI2_HOST;

    /*
     * Monta o FAT filesystem.
     */
    sdmmc_card_t *card;

    esp_vfs_fat_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    ret = esp_vfs_fat_sdspi_mount(
        MOUNT_POINT,
        &host,
        &slot_config,
        &mount_config,
        &card
    );

    if (ret != ESP_OK)
    {
        printf("Erro ao montar o SD: %s\n",
               esp_err_to_name(ret));
        return;
    }

    printf("Cartao SD montado!\n");
}

void	app_main(void)
{
	DIR *dir = opendir("/sdcard");

	if (dir == NULL)
	{
		printf("Nao foi possivel abrir o diretorio\n");
		return;
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
}