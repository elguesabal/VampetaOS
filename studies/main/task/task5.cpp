#include "../studies.hpp"

void	handler1(void *arg) {
	vTaskDelay(pdMS_TO_TICKS(100));
	while (true) {
		printf("handler1\n");
		taskYIELD();
	}
}

void	handler2(void *arg) {
	while (true) {
		printf("handler2\n");
		taskYIELD();
	}
}

void	task5(void) {
	xTaskCreate(handler1, "handler1", 4094, NULL, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, NULL, 1, NULL);
}