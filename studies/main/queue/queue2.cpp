#include "../studies.hpp"

QueueHandle_t queue;

void	task(void *arg) {
	char str[10];
	xQueueReceive(queue, str, portMAX_DELAY);
	printf("queue ---> %s\n", str);
	vTaskDelete(NULL);
}

void	queue2(void) {
	// queue = xQueueCreate(10, sizeof(char)); // NAO ENTENDI PQ ASSIM NAO FUNCIONA
	queue = xQueueCreate(10, 10);
	xTaskCreate(task, "task", 4094, NULL, 1, NULL);
	char str[] = "VampetaOS";
	sleep(5);
	xQueueSend(queue, str, portMAX_DELAY);
}