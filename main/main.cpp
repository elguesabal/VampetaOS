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

extern "C" void	app_main(void) {
// printf("RAM livre: %u KB\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024);
	if (!Sd::sd_init()) return;

const char *test = Sd::create_dir("/sdcard/VampetaOS/test/test");
// const char *test = Sd::create_dir("/sdcard/!!!!!");
printf("test -> %s\n", test);
write(1, "\n\n\n", 3);

// if (!Sd::exist_dir("/sdcard/VampetaOS")) {
// 	printf("nao existe\n");
// 	if (Sd::create_dir("/sdcard/VampetaOS")) printf("criado\n");
// } else {
// 	printf("existe\n");
// }
// write(1, "\n\n\n", 3);

std::vector<DirectoryEntry>	ls = Sd::list_dir("/sdcard");
for (const DirectoryEntry& entry : ls) printf("%s\n", entry.name.c_str());
write(1, "\n\n\n", 3);

	// while (1) {
	// 	write(1, "VampetaOS\n", 10);
	// 	sleep(1);
	// }
}