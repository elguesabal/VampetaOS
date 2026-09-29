/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /sd/sd.hpp                                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef SD_H
#define SD_H

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <string>
#include <vector>

#include "esp_err.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"

#define SCK			GPIO_NUM_40
#define MISO		GPIO_NUM_39
#define MOSI		GPIO_NUM_14
#define CS			GPIO_NUM_12
#define MOUNT_POINT	"/sdcard"
#define DIR_SYSTEM	"/VampetaOS"

/**
 * @author elguesabal
 * @brief GUARDA NOME E SE E UM DIRETORIO (USADO PARA LISTAGEM DE DIRETORIO)
*/
struct DirectoryEntry
{
	std::string	name;
	bool 		isDirectory;
};

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O CARTAO DE MEMORIA
*/
class Sd {
	public:
		static bool							sd_init(void);
		static bool							exist_dir(const char *path);
		static bool							exist_file(const char *path);
		static bool							create_dir(const char *path);
		static bool							remove_dir(const char *path);
		static bool							create_file(const char *path);
		static std::vector<DirectoryEntry>	list_dir(const char *path);

	private:
		static std::string					full_path(const char *path);
};

#endif