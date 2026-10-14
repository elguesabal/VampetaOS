/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /main.c                                                                   |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  test                                                                      |
  |  app_main                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "VampetaOS.hpp"

#include "Sd/Sd.hpp"
#include "System/System.hpp"
#include "Wifi/Wifi.hpp"

// #include "esp_heap_caps.h"
// #include "freertos/task.h"

// void task_example(void *arg)
// {
//     while (1) {
//         printf("Minha task está executando\n");
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

/**
 * @author elguesabal
 * @brief FUNCAO DE TESTES
*/
void	test(void) {
// printf("RAM livre: %u KB\n\n\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024);

// if (!Sd::create_dir("/directory")) printf("reate_dir -> %s\n\n\n", strerror(errno));

// if (!Sd::remove_dir("/directory")) printf("remove_dir -> %s\n\n\n", strerror(errno));

// if (Sd::exist_dir("/directory")) printf("existe este diretorio\n\n\n");

// if (!Sd::create_file("/file")) printf("create_file -> %s\n\n\n", strerror(errno));

// if (!Sd::create_file("/file.txt", "VampetaOS")) printf("create_file -> %s\n\n\n", strerror(errno));

// if (!Sd::write_file("/file.txt", "VampetaOS")) printf("write_file -> %s\n\n\n", strerror(errno));

// if (!Sd::set_config("/Wifi/WIFI_CONFIG", "WIFI", "VampetaOS")) printf("set_config -> %s\n\n\n", strerror(errno));

// std::string wifi = Sd::get_config("/Wifi/WIFI_CONFIG", "WIFI");
// if (!wifi.empty()) {
// 	printf("%s\n", wifi.c_str());
// } else if (errno) {
// 	printf("get_config -> %s\n\n\n", strerror(errno));
// } else if (errno == 0) {
// 	printf("errno == 0");
// }
// printf("\n\n\n");

// std::vector<Sd::DirectoryEntry>	ls = Sd::list_dir("/");
// if (errno != 0) {
// 	printf("list_dir -> %s\n\n\n", strerror(errno));
// } else if (!ls.empty()) {
// 	for (const Sd::DirectoryEntry& entry : ls) printf("%s\n\n\n", entry.name.c_str());
// 	printf("\n\n\n");
// }

// if (!Sd::delete_dir("/test")) printf("delete_dir -> %s\n\n\n", strerror(errno));

// std::string wifi_config;
// if (!Sd::read_file("/Wifi/WIFI_CONFIG", wifi_config)) printf("read_file -> %s\n\n\n", strerror(errno));
// printf("%s\n\n\n", wifi_config.c_str());
// printf("\n\n\n");

// printf("SSID -> \"%s\"\n", Wifi::get_ssid().c_str());
// printf("PASSWORD -> \"%s\"\n", Wifi::get_password().c_str());
// printf("\n\n\n");

// xTaskCreate(
//     task_example,   // Função de entrada
//     "task_example", // Nome
//     2048,           // Stack em bytes no ESP-IDF
//     NULL,           // Parâmetro da task
//     5,              // Prioridade
//     NULL            // Handle opcional
// );
}

/**
 * @author elguesabal
 * @brief FUNCAO PRINCIPAL
*/
extern "C" void	app_main(void) {
	if (!Sd::init_sd()) return;
	if (!System::init_system()) return;
	if (!Wifi::init_wifi()) return;

	test();

	printf("VampetaOS\n");
}