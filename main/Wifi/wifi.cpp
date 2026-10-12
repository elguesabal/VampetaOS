/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Wifi/wifi.cpp                                                            |
  |                                                                            |
  |  elguesabal@VampetaOS:~$ functions                                         |
  |  init_wifi                                                                 |
  |  init_dir                                                                  |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#include "Wifi.hpp"



#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
#define WIFI_MAX_RETRIES   5

static EventGroupHandle_t wifi_event_group;
static int retry_count = 0;



std::string Wifi::ssid = "";
std::string Wifi::password = "";

/**
 * @author elguesabal
 * @brief INICIA O WIFI
 * @return RETORNA true EM CASO DE WIFI INICIADO COM SUCESSO
 * @return RETORNA false CASO init_dir FALHE
*/
bool	Wifi::init_wifi(void) {
	if (!Wifi::init_dir()) return (false);
	if (!Wifi::connect()) {
		// printf("VampetaOS: Wi-Fi initialization failed\n");
		return (false);
	}
	return (true);
}

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
bool	Wifi::init_dir(void) {
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





void	Wifi::wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    (void)arg;
    (void)event_data;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_count < WIFI_MAX_RETRIES) {
            retry_count++;
            esp_wifi_connect();
        } else {
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        retry_count = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

bool	Wifi::connect(void) {
    if (Wifi::ssid.empty()) {
        printf("SSID is empty\n");
        return (false);
    }
    // if (Wifi::ssid.size() > sizeof(wifi_config_t().sta.ssid) ||
    //     Wifi::password.size() > sizeof(wifi_config_t().sta.password))
    // {
    //     printf("Invalid Wi-Fi credentials length\n");
    //     return false;
    // }
    wifi_event_group = xEventGroupCreate();
    if (wifi_event_group == NULL) {
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
    ret = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    if (ret != ESP_OK) {
        printf("Failed to register Wi-Fi handler: %s\n", esp_err_to_name(ret));
        return (false);
    }
    ret = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    if (ret != ESP_OK) {
        printf("Failed to register IP handler: %s\n", esp_err_to_name(ret));
        return (false);
    }
    wifi_config_t config = {};
    memcpy(config.sta.ssid, Wifi::ssid.c_str(), Wifi::ssid.size());
    memcpy(config.sta.password, Wifi::password.c_str(), Wifi::password.size());
    ret = esp_wifi_set_mode(WIFI_MODE_STA);
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
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(20000));
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