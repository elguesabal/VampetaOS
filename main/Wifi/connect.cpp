/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VampetaOs  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/connect.cpp                                                         |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init                                                                      |
  |  wifi_event_handler                                                        |
  |  register_events                                                           |
  |  connect                                                                   |
  |  connect                                                                   |
  |  disconnect                                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

/**
 * @author elguesabal
 * @brief INICIALIZA A INFRAESTRUTURA NECESSARIA PARA O WIFI
 * @return RETORNA true CASO A INICIALIZACAO SEJA REALIZADA COM SUCESSO
 * @return RETORNA false CASO xEventGroupCreate FALHE
 * @return RETORNA false CASO esp_netif_init FALHE
 * @return RETORNA false CASO esp_event_loop_create_default FALHE
 * @return RETORNA false CASO esp_netif_create_default_wifi_sta FALHE
 * @return RETORNA false CASO esp_wifi_init FALHE
*/
bool	Wifi::init(void) {
	Wifi::wifi_event_group = xEventGroupCreate();
	if (Wifi::wifi_event_group == NULL) {
		printf("Failed to create Wi-Fi event group\n");
		return (false);
	}
	esp_err_t ret = esp_netif_init();
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_event_loop_create_default();
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
	if (sta_netif == NULL) {
		printf("Failed to create default Wi-Fi STA interface\n");
		return (false);
	}
	wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
	ret = esp_wifi_init(&init_config);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief PROCESSA EVENTOS DA INTERFACE WIFI E DA OBTENCAO DE ENDERECO IP
 * @param arg PONTEIRO PARA UM ARGUMENTO PERSONALIZADO PASSADO AO REGISTRAR O HANDLER DE EVENTOS
 * @param event_base BASE DO EVENTO QUE IDENTIFICA A CATEGORIA DO EVENTO RECEBIDO, COMO WIFI_EVENT OU IP_EVENT
 * @param event_id IDENTIFICADOR DO EVENTO ESPECIFICO QUE OCORREU, COMO WIFI_EVENT_STA_START, WIFI_EVENT_STA_DISCONNECTED OU IP_EVENT_STA_GOT_IP
 * @param event_data PONTEIRO PARA OS DADOS ASSOCIADOS AO EVENTO RECEBIDO, QUANDO DISPONIVEIS
*/
void	Wifi::wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
	(void)arg;
	(void)event_data;
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
		esp_wifi_connect();
	} else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
		if (Wifi::retry_count < WIFI_MAX_RETRIES) {
			Wifi::retry_count++;
			esp_wifi_connect();
		} else {
			xEventGroupSetBits(Wifi::wifi_event_group, WIFI_FAIL_BIT);
		}
	} else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
		Wifi::retry_count = 0;
		xEventGroupSetBits(Wifi::wifi_event_group, WIFI_CONNECTED_BIT);
	}
}

/**
 * @author elguesabal
 * @brief REGISTRA OS MANIPULADORES DE EVENTOS DO WIFI E DO IP
 * @return RETORNA true EM CASO DE EVENTO REGISTRADO COM SUCESSO
 * @return RETORNA false CASO esp_event_handler_register FALHE
*/
bool	Wifi::register_events(void) {
	esp_err_t ret = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, Wifi::wifi_event_handler, NULL);
	if (ret != ESP_OK) {
		printf("Failed to register Wi-Fi handler: %s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, Wifi::wifi_event_handler, NULL);
	if (ret != ESP_OK) {
		printf("Failed to register IP handler: %s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}

/**
 * @author elguesabal
 * @brief CONFIGURA A INTERFACE STA, INICIA O WIFI E AGUARDA A CONEXAO COM A REDE CONFIGURADA
 * @details UTILIZA OS VALORES ARMAZENADOS EM Wifi::ssid E Wifi::password
 * @return RETORNA true EM CASO DE REDE WIFI CONECTADO COM SUCESSO
 * @return RETORNA false CASO esp_wifi_set_mode FALHE
 * @return RETORNA false CASO esp_wifi_set_config FALHE
 * @return RETORNA false CASO esp_wifi_start FALHE
 * @return RETORNA false CASO xEventGroupWaitBits FALHE
*/
bool	Wifi::connect(void) {
	wifi_config_t config = {};
	memcpy(config.sta.ssid, Wifi::ssid.c_str(), Wifi::ssid.size());
	memcpy(config.sta.password, Wifi::password.c_str(), Wifi::password.size());
	esp_err_t ret = esp_wifi_set_mode(WIFI_MODE_STA);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_wifi_set_config(WIFI_IF_STA, &config);
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_wifi_start();
	if (ret != ESP_OK) {
		printf("%s\n", esp_err_to_name(ret));
		return (false);
	}
	EventBits_t bits = xEventGroupWaitBits(Wifi::wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(20000));
	if (bits & WIFI_CONNECTED_BIT) {
		printf("Wi-Fi connected: %s\n", Wifi::ip().c_str());
		return (true);
	}
	if (bits & WIFI_FAIL_BIT) {
		printf("Failed to connect to Wi-Fi\n");
	} else {
		printf("Wi-Fi connection timeout\n");
	}
	return (false);
}

// bool	Wifi::connect(const char *ssid, const char *password) {
// 	if (!Wifi::set_ssid(ssid)) return (false);
// 	if (!Wifi::set_password(password)) return (false);
// 	return (Wifi::connect());
// }

// bool	Wifi::disconnect(void) {

// }

/**
 * @author elguesabal
 * @brief IDENTIFICA O ATUAL IP DO ESP
 * @return RETORNA O ENDERECO IPV4 EM CASO DE SUCESSO
 * @return RETORNA UMA STRING VAZIA EM CASO DE FALHA OU NENHUMA REDE CONECTADA
*/
std::string	Wifi::ip(void) {
	esp_netif_ip_info_t ip_info = {};
	esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
	if (netif != nullptr && esp_netif_get_ip_info(netif, &ip_info) == ESP_OK) {
		char ip[16] = {};
		if (esp_ip4addr_ntoa(&ip_info.ip, ip, sizeof(ip)) != nullptr) return (std::string(ip));
	}
	return ("");
}