#include "../studies.hpp"

void	handler(void *arg) {
	while (true) {
		printf("handler\n");
		sleep(1);
	}
}

void	task3(void) {
	xTaskCreate(handler, "handler", 4094, NULL, 5, NULL);
}