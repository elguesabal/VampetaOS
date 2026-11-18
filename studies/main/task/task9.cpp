#include "../studies.hpp"

SemaphoreHandle_t semaphore1;
SemaphoreHandle_t semaphore2;

void	handler1(void *arg) {
	while (true) {
		printf("task1\n");
		xSemaphoreGive(semaphore2);
		xSemaphoreTake(semaphore1, portMAX_DELAY);
	}
}

void	handler2(void *arg) {
	while (true) {
		xSemaphoreTake(semaphore2, portMAX_DELAY);
		printf("task2\n");
		xSemaphoreGive(semaphore1);
	}
}

void	task9(void) {
	semaphore1 = xSemaphoreCreateBinary();
	semaphore2 = xSemaphoreCreateBinary();
	xSemaphoreGive(semaphore1);
	xTaskCreate(handler1, "handler1", 4094, NULL, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, NULL, 1, NULL);
}