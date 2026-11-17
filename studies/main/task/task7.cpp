#include "../studies.hpp"

SemaphoreHandle_t mutex;

void	handler1(void *arg) {
	vTaskDelay(pdMS_TO_TICKS(100));
	char *str = (char *)arg;
	while (true) {
		xSemaphoreTake(mutex, portMAX_DELAY);
		str[3] = '1';
		printf("task1 --> %s\n", str);
		xSemaphoreGive(mutex);
		taskYIELD();
	}
}

void	handler2(void *arg) {
	char *str = (char *)arg;
	while (true) {
		xSemaphoreTake(mutex, portMAX_DELAY);
		str[3] = '2';
		printf("task2 --> %s\n", str);
		xSemaphoreGive(mutex);
		taskYIELD();
	}
}

void	task7(void) {
	mutex = xSemaphoreCreateMutex();
	char *arg = (char *)malloc(5 * sizeof(char));
	arg[0] = 'a';
	arg[1] = 'b';
	arg[2] = 'c';
	arg[3] = '\0';
	arg[4] = '\0';
	xTaskCreate(handler1, "handler1", 4094, arg, 1, NULL);
	xTaskCreate(handler2, "handler2", 4094, arg, 1, NULL);
}