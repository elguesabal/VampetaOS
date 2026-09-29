/*
+ -------------------------------------------------------------------------- +
|  o o o                                                          VAMPETAOS  |
+ -------------------------------------------------------------------------- +
|                                                                            |
|  elguesabal@VampetaOS:~$ pwd                                               |
|  /main.c                                                                   |
|                                                                            |
|  elguesabal@VampetaOS:~$ functions                                         |
|  app_main                                                                  |
|                                                                            |
+ -------------------------------------------------------------------------- +
*/

#include "sd/sd.hpp"

#include <stdio.h>
#include <unistd.h>

#include <string>
#include <vector>

// #include "esp_heap_caps.h"

/**
* @author elguesabal
* @brief FUNCAO PRINCIPAL
*/
extern "C" void	app_main(void) {
// printf("RAM livre: %u KB\n\n\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024);
	if (!Sd::sd_init()) {
		printf("%s\n", strerror(errno));
		return;
	}

// if (!Sd::create_dir("/directory")) printf("reate_dir -> %s\n\n\n", strerror(errno));

// if (!Sd::remove_dir("/directory")) printf("remove_dir -> %s\n\n\n", strerror(errno));

// if (Sd::exist_dir("/directory")) printf("existe este diretorio\n\n\n");

// if (!Sd::create_file("/file123")) printf("create_file -> %s\n\n\n", strerror(errno));

std::vector<DirectoryEntry>	ls = Sd::list_dir("/");
for (const DirectoryEntry& entry : ls) printf("%s\n", entry.name.c_str());
write(1, "\n\n\n", 3);

	write(1, "VampetaOS\n", 10);
	// while (1) {
	// 	write(1, "VampetaOS\n", 10);
	// 	sleep(1);
	// }
}