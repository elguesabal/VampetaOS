/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
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
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"

bool	Wifi::init(void) {
	Wifi::wifi_event_group = xEventGroupCreate();
	if (Wifi::wifi_event_group == NULL) {
		printf("Failed to create Wi-Fi event group\n");
		return (false);
	}
	esp_err_t ret = esp_netif_init();
	if (ret != ESP_OK) {
		printf("esp_netif_init: %s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_event_loop_create_default();
	if (ret != ESP_OK) {
		printf("esp_event_loop_create_default: %s\n", esp_err_to_name(ret));
		return (false);
	}
	esp_netif_create_default_wifi_sta();
	wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
	ret = esp_wifi_init(&init_config);
	if (ret != ESP_OK) {
		printf("esp_wifi_init: %s\n", esp_err_to_name(ret));
		return (false);
	}
	return (true);
}

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

bool	Wifi::connect(void) {
	wifi_config_t config = {};
	memcpy(config.sta.ssid, Wifi::ssid.c_str(), Wifi::ssid.size());
	memcpy(config.sta.password, Wifi::password.c_str(), Wifi::password.size());
	esp_err_t ret = esp_wifi_set_mode(WIFI_MODE_STA);
	if (ret != ESP_OK) {
		printf("esp_wifi_set_mode: %s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_wifi_set_config(WIFI_IF_STA, &config);
	if (ret != ESP_OK) {
		printf("esp_wifi_set_config: %s\n", esp_err_to_name(ret));
		return (false);
	}
	ret = esp_wifi_start();
	if (ret != ESP_OK) {
		printf("esp_wifi_start: %s\n", esp_err_to_name(ret));
		return (false);
	}
	EventBits_t bits = xEventGroupWaitBits(Wifi::wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(20000));
	if (bits & WIFI_CONNECTED_BIT) {
		printf("Wi-Fi connected\n");
		return (true);
	}
	if (bits & WIFI_FAIL_BIT) {
		printf("Failed to connect to Wi-Fi\n");
	} else {
		printf("Wi-Fi connection timeout\n");
	}
	return (false);
}

bool	Wifi::connect(const char *ssid, const char *password) {
	if (!Wifi::set_ssid(ssid)) return (false);
	if (!Wifi::set_password(password)) return (false);
	return (Wifi::connect());
}

// VERIFICAR SE TEM COMO VER SE A NVS ESTA INICIAR
// ENTENDER MELHOR O CODIGO E VER SE ESTOU ERRANDO
// RENOMEAR METODOS E PENSAR MELHOR NA ESTRUTURA
// ENTENDER MELHOR COMO O FreeRTOS FUNCIONA E SUA ASYNC