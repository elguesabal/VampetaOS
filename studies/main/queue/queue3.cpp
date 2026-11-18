#include "../studies.hpp"

QueueHandle_t queue;

void	task(void *arg) {
	char *str = nullptr;
	// xQueueReceive(queue, str, portMAX_DELAY);
	// printf("queue ---> %s\n", str);
if (xQueueReceive(queue, &str, portMAX_DELAY) == pdPASS) {
	if (str != nullptr) {
		printf("queue ---> %s\n", str);
	}
}
	vTaskDelete(NULL);
}

void	queue2(void) {
	queue = xQueueCreate(10, sizeof(char *));
	xTaskCreate(task, "task", 4094, NULL, 1, NULL);
	static char str[] = "VampetaOS";
	sleep(5);
	xQueueSend(queue, &str, portMAX_DELAY);
}