#include "../studies.hpp"

void	handler(void *arg) {
	while (true) {
		printf("handler\n");
		sleep(1);
	}
}

void	task2(void) {
	xTaskCreate(handler, "handler", 4094, NULL, 1, NULL);
}