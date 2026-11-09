/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/directory.cpp                                                       |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  check_dir                                                                 |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

/**
 * @author elguesabal
 * @brief VERIFICA SE O ARQUIVO DE CONFIGURACAO DO WIFI EXISTE E CRIA CASO NAO
 * @return RETORNA true CASO /VampetaOS/wifi/WIFI_CONFIG EXISTA E ESTEJA CONFIGURADO CORRETAMENTE
 * @return RETORNA false CASO /VampetaOS/wifi SEJA UM ARQUIVO
 * @return RETORNA false CASO /VampetaOS/wifi NAO EXISTA E FALHE NA CRIACAO
 * @return RETORNA false CASO /VampetaOS/wifi/WIFI_CONFIG SEJA UM DIRETORIO
 * @return RETORNA false CASO A FUNCAO get_config RETORNE GERE UM ERRO AO BUSCAR "WIFI"
 * @return RETORNA false CASO A CONFIGURACAO "WIFI" EM /VampetaOS/wifi/WIFI_CONFIG ESTEJA VAZIO OU NAO EXISTA
 * @return RETORNA false CASO A CONFIGURACAO "WIFI" EM /VampetaOS/wifi/WIFI_CONFIG CONTENHA UM WIFI INVALIDO
 * @return RETORNA false CASO A FUNCAO get_config RETORNE GERE UM ERRO AO BUSCAR "PASSWORD"
 * @return RETORNA false CASO A CONFIGURACAO "PASSWORD" EM /VampetaOS/wifi/WIFI_CONFIG CONTENHA UM PASSWORD INVALIDO (ACEITA STRING VAZIA OU "PASSWORD NAO EXISTENTE")
 * @return RETORNA false CASO /VampetaOS/wifi/WIFI_CONFIG NAO EXISTA E FALHE NA CRIACAO
 * @return RETORNA false CASO /VampetaOS/wifi/WIFI_CONFIG NAO EXISTA E SEJA CRIADO (SEM CREDENCIAIS CONFIGURADAS)
*/
bool	Wifi::check_dir(void) {
	if (!Sd::exist_dir("/wifi")) {
		if (Sd::exist_file("/wifi")) {
			printf("/VampetaOS/wifi must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/wifi")) {
			printf("Failed to create /VampetaOS/wifi: %s\n", strerror(errno));
			return (false);
		}
	}
	if (Sd::exist_file("/wifi/WIFI_CONFIG")) {
		std::string ssid = Sd::get_config("/wifi/WIFI_CONFIG", "WIFI");
		if (ssid.empty()) {
			if (errno == 0) {
				printf("The \"WIFI\" field must be configured in /VampetaOS/wifi/WIFI_CONFIG.\n");
			} else {
				printf("Failed to obtain \"WIFI\": %s\n", strerror(errno));
			}
			return (false);
		}
		if (!Wifi::set_ssid(ssid.c_str())) {
			printf("Invalid \"WIFI\"\n");
			return (false);
		}
		std::string password = Sd::get_config("/wifi/WIFI_CONFIG", "PASSWORD");
		if (errno != 0) {
			printf("Failed to obtain \"PASSWORD\": %s\n", strerror(errno));
			return (false);
		}
		if (!Wifi::set_password(password.c_str())) {
			printf("Invalid \"PASSWORD\"\n");
			return (false);
		}
		return (true);
	}
	if (Sd::exist_dir("/wifi/WIFI_CONFIG")) {
		printf("/wifi/WIFI_CONFIG must be a file\n");
		return (false);
	}
	if (!Sd::create_file("/wifi/WIFI_CONFIG", "WIFI=\"\"\nPASSWORD=\"\"")) {
		printf("Failed to create /wifi/WIFI_CONFIG: %s\n", strerror(errno));
		return (false);
	}
	printf("Enter valid Wi-Fi details in the /VampetaOS/wifi/WIFI_CONFIG file\n");
	return (false);
}