#include <stdio.h>

#include "nvs_flash.h"

#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_err.h"

void app_main(void)
{
    esp_err_t err;

    /*
     * 1. Inicializa NVS.
     *
     * O Wi-Fi usa NVS para armazenar algumas configurações.
     */
    err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
        err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK(err);


    /*
     * 2. Inicializa a camada de rede.
     */
    ESP_ERROR_CHECK(esp_netif_init());


    /*
     * 3. Cria o event loop padrão.
     */
    ESP_ERROR_CHECK(esp_event_loop_create_default());


    /*
     * 4. Cria a interface Wi-Fi em modo Station.
     */
    esp_netif_create_default_wifi_sta();


    /*
     * 5. Configuração padrão do driver Wi-Fi.
     */
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));


    /*
     * 6. Coloca o Wi-Fi em modo Station.
     */
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));


    /*
     * 7. Inicia o Wi-Fi.
     */
    ESP_ERROR_CHECK(esp_wifi_start());


    printf("\n");
    printf("Iniciando scan Wi-Fi...\n");
    printf("\n");


    /*
     * 8. Faz o scan.
     *
     * NULL = configuração padrão.
     * true = espera o scan terminar.
     */
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));


    /*
     * 9. Descobre quantas redes foram encontradas.
     */
    uint16_t ap_count = 0;

    ESP_ERROR_CHECK(
        esp_wifi_scan_get_ap_num(&ap_count)
    );

    printf("Redes encontradas: %u\n\n", ap_count);


    /*
     * 10. Limita a quantidade de redes que vamos armazenar.
     */
    uint16_t max_records = 20;

    if (ap_count < max_records)
        max_records = ap_count;


    wifi_ap_record_t records[20];


    /*
     * 11. Obtém as informações das redes encontradas.
     */
    ESP_ERROR_CHECK(
        esp_wifi_scan_get_ap_records(&max_records, records)
    );


    /*
     * 12. Mostra os resultados.
     */
    for (int i = 0; i < max_records; i++)
    {
        printf(
            "%2d | %-32s | RSSI: %4d | Canal: %2d\n",
            i + 1,
            (char *)records[i].ssid,
            records[i].rssi,
            records[i].primary
        );
    }

    printf("\nScan terminado.\n");
}