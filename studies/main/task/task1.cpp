#include "../studies.hpp"

void	handler(void *arg) {
	printf("handler\n");
	vTaskDelete(NULL);
}

void	task1(void) {
	xTaskCreate(handler, "handler", 4094, NULL, 1, NULL);
}