#include "../studies.hpp"

QueueHandle_t queue;

void task(void *arg) {
    char *str = nullptr;
    if (xQueueReceive(queue, &str, portMAX_DELAY) == pdPASS) {
        printf("queue ---> %s\n", str);
    }
    vTaskDelete(NULL);
}

void queue3(void) {
    queue = xQueueCreate(10, sizeof(char *));
    xTaskCreate(task, "task", 4094, NULL, 1, NULL);
    static char str[] = "VampetaOS";
    char *ptr = str;
	sleep(5);
    xQueueSend(queue, &ptr, portMAX_DELAY);
}