#include "../studies.hpp"

void	handler1(void *arg) {
	while (true) {
		printf("handler1\n");
		sleep(1);
	}
}

void	handler2(void *arg) {
	while (true) {
		printf("handler2\n");
		sleep(1);
	}
}

void	task4(void) {
	xTaskCreate(handler1, "handler1", 4094, NULL, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, NULL, 1, NULL);
}