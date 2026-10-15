/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
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
 * @return RETORNA true CASO /VampetaOS/Wifi/WIFI_CONFIG EXISTA E ESTEJA CONFIGURADO CORRETAMENTE
 * @return RETORNA false CASO /VampetaOS/Wifi SEJA UM ARQUIVO
 * @return RETORNA false CASO /VampetaOS/Wifi NAO EXISTA E FALHE NA CRIACAO
 * @return RETORNA false CASO /VampetaOS/Wifi/WIFI_CONFIG SEJA UM DIRETORIO
 * @return RETORNA false CASO A FUNCAO get_config RETORNE GERE UM ERRO AO BUSCAR "WIFI"
 * @return RETORNA false CASO A CONFIGURACAO "WIFI" EM /VampetaOS/Wifi/WIFI_CONFIG ESTEJA VAZIO OU NAO EXISTA
 * @return RETORNA false CASO A CONFIGURACAO "WIFI" EM /VampetaOS/Wifi/WIFI_CONFIG CONTENHA UM WIFI INVALIDO
 * @return RETORNA false CASO A FUNCAO get_config RETORNE GERE UM ERRO AO BUSCAR "PASSWORD"
 * @return RETORNA false CASO A CONFIGURACAO "PASSWORD" EM /VampetaOS/Wifi/WIFI_CONFIG CONTENHA UM PASSWORD INVALIDO (ACEITA STRING VAZIA OU "PASSWORD NAO EXISTENTE")
 * @return RETORNA false CASO /VampetaOS/Wifi/WIFI_CONFIG NAO EXISTA E FALHE NA CRIACAO
 * @return RETORNA false CASO /VampetaOS/Wifi/WIFI_CONFIG NAO EXISTA E SEJA CRIADO (SEM CREDENCIAIS CONFIGURADAS)
*/
bool	Wifi::check_dir(void) {
	if (!Sd::exist_dir("/Wifi")) {
		if (Sd::exist_file("/Wifi")) {
			printf("/VampetaOS/Wifi must be a directory\n");
			return (false);
		}
		if (!Sd::create_dir("/Wifi")) {
			printf("Failed to create /VampetaOS/Wifi: %s\n", strerror(errno));
			return (false);
		}
	}
	if (Sd::exist_file("/Wifi/WIFI_CONFIG")) {
		std::string ssid = Sd::get_config("/Wifi/WIFI_CONFIG", "WIFI");
		if (ssid.empty()) {
			if (errno == 0) {
				printf("The \"WIFI\" field must be configured in /VampetaOS/Wifi/WIFI_CONFIG.\n");
			} else {
				printf("Failed to obtain \"WIFI\": %s\n", strerror(errno));
			}
			return (false);
		}
		if (!Wifi::set_ssid(ssid.c_str())) {
			printf("Invalid \"WIFI\"\n");
			return (false);
		}
		std::string password = Sd::get_config("/Wifi/WIFI_CONFIG", "PASSWORD");
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