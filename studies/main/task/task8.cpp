#include "../studies.hpp"

void	handler1(void *arg) {
	while (true) {
		printf("task1\n");
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void	handler2(void *arg) {
	while (true) {
		printf("task2\n");
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void	task8(void) {
	xTaskCreate(handler1, "handler1", 4094, NULL, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, NULL, 1, NULL);
}