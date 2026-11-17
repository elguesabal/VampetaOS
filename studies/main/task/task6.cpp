#include "../studies.hpp"

void	handler1(void *arg) {
	vTaskDelay(pdMS_TO_TICKS(100));
	char *str = (char *)arg;
	while (true) {
		str[3] = '1';
		printf("task1 --> %s\n", str);
		taskYIELD();
	}
}

void	handler2(void *arg) {
	char *str = (char *)arg;
	while (true) {
		str[3] = '2';
		printf("task2 --> %s\n", str);
		taskYIELD();
	}
}

void	task6(void) {
	char *arg = (char *)malloc(5 * sizeof(char));
	arg[0] = 'a';
	arg[1] = 'b';
	arg[2] = 'c';
	arg[3] = '\0';
	arg[4] = '\0';
	xTaskCreate(handler1, "handler1", 4094, arg, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, arg, 1, NULL);
}