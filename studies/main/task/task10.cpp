#include "../studies.hpp"

SemaphoreHandle_t semaphore;

void	handler1(void *arg) {
	while (true) {
		printf("task1\n");
		xSemaphoreGive(semaphore);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void	handler2(void *arg) {
	while (true) {
		xSemaphoreTake(semaphore, portMAX_DELAY);
		printf("task2\n");
	}
}

void	task10(void) {
	semaphore = xSemaphoreCreateBinary();
	xTaskCreate(handler1, "handler1", 4094, NULL, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, NULL, 1, NULL);
}