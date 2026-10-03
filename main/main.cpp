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

#include "Sd/Sd.hpp"
#include "System/System.hpp"
#include "Wifi/Wifi.hpp"

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
	if (!Sd::init_sd()) return;
	if (!System::init_system()) return;
	if (!Wifi::init_wifi()) return;

// if (!Sd::create_dir("/directory")) printf("reate_dir -> %s\n\n\n", strerror(errno));

// if (!Sd::remove_dir("/directory")) printf("remove_dir -> %s\n\n\n", strerror(errno));

// if (Sd::exist_dir("/directory")) printf("existe este diretorio\n\n\n");

// if (!Sd::create_file("/file")) printf("create_file -> %s\n\n\n", strerror(errno));

// if (!Sd::create_file("/file.txt", "VampetaOS")) printf("create_file -> %s\n\n\n", strerror(errno));

// if (!Sd::write_file("/file.txt", "VampetaOS")) printf("write_file -> %s\n\n\n", strerror(errno));

// std::vector<DirectoryEntry>	ls = Sd::list_dir("/");
// for (const DirectoryEntry& entry : ls) printf("%s\n", entry.name.c_str());
// write(1, "\n\n\n", 3);

	write(1, "VampetaOS\n", 10);
	// while (1) {
	// 	write(1, "VampetaOS\n", 10);
	// 	sleep(1);
	// }
  // write(1, "Windows\n", 8);
  write(1, "Linux\n", 6);
}