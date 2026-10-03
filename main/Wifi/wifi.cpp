/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/Wifi.cpp                                                            |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_wifi                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

/**
* @author elguesabal
* @brief VERIFICA SE O ARQUIVO DE CONFIGURACAO DO WIFI EXISTE E CRIA CASO NAO
* @return RETORNA true CASO /Wifi/WIFI_CONFIG EXISTA E ESTEJA CONFIGURADO CORRETAMENTE
* @return RETORNA false CASO /Wifi SEJA UM ARQUIVO
* @return RETORNA false CASO /Wifi NAO EXISTA E FALHE NA CRIACAO
* @return RETORNA false CASO /Wifi/WIFI_CONFIG SEJA UM DIRETORIO
* @return RETORNA false CASO /Wifi/WIFI_CONFIG NAO EXISTA E FALHE NA CRIACAO
* @return RETORNA false CASO /Wifi/WIFI_CONFIG NAO EXISTA E SEJA CRIADO (SEM CREDENCIAIS CONFIGURADAS)
*/
bool	Wifi::init_wifi(void) {
	// std::string wifi_dir = System::full_path("/Wifi");
	// std::string wifi_config = System::full_path("/Wifi/WIFI_CONFIG");
	// struct stat info;
	// if (stat(wifi_dir.c_str(), &info) == 0) {
	// 	if (!S_ISDIR(info.st_mode)) {
	// 		printf("%s must be a directory\n", wifi_dir.c_str());
	// 		return (false);
	// 	}
	// }
	// else {
	// 	if (errno != ENOENT) {
	// 		printf("%s\n", strerror(errno));
	// 		return (false);
	// 	}
	// 	if (!Sd::create_dir("/Wifi")) {
	// 		printf("%s\n", strerror(errno));
	// 		return (false);
	// 	}
	// }
	// if (stat(wifi_config.c_str(), &info) == 0) {
	// 	if (!S_ISREG(info.st_mode)) {
	// 		printf("%s must be a file\n", wifi_config.c_str());
	// 		return (false);
	// 	}
	// 	// FALTA VERIFICA SE O ARQUIVO ESTA PREENCHIDO CORRETAMENTE MAS VOU FAZER ISSO DEPOIS
	// 	printf("Wifi: OK\n");
	// 	return (true);
	// }
	// if (errno != ENOENT) {
	// 	printf("%s\n", strerror(errno));
	// 	return (false);
	// }
	// if (!Sd::create_file("/Wifi/WIFI_CONFIG", "WIFI=\"\"\nPASSWORD=\"\"")) {
	// 	printf("%s\n", strerror(errno));
	// 	return (false);
	// }
	// printf("Enter valid Wi-Fi details in the /VampetaOS/Wifi/WIFI_CONFIG file\n");
	// return (false);

	if (!Sd::exist_dir("/Wifi")) {
		if (Sd::exist_file("/Wifi")) {
			printf("/Wifi must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/Wifi")) {
			printf("Failed to create /Wifi: %s\n", strerror(errno));
			return (false);
		}
	}
	if (Sd::exist_file("/Wifi/WIFI_CONFIG")) {
		// FALTA VERIFICAR SE O ARQUIVO ESTA PREENCHIDO CORRETAMENTE
		printf("Wifi: OK\n");
		return (true);
	}
	if (Sd::exist_dir("/Wifi/WIFI_CONFIG")) {
		printf("/Wifi/WIFI_CONFIG must be a file\n");
		return (false);
	}
	if (!Sd::create_file("/Wifi/WIFI_CONFIG", "WIFI=\"\"\nPASSWORD=\"\"")) {
		printf("Failed to create /Wifi/WIFI_CONFIG: %s\n", strerror(errno));
		return (false);
	}
	printf("Enter valid Wi-Fi details in the /VampetaOS/Wifi/WIFI_CONFIG file\n");
	return (false);
}