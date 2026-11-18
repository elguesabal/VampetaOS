#include "../studies.hpp"

QueueHandle_t queue;

void	queue1(void) {
	queue = xQueueCreate(1, sizeof(int));
	int n = 42;
	xQueueSend(queue, &n, portMAX_DELAY);
	int arg;
	xQueueReceive(queue, &arg, portMAX_DELAY);
	printf("queue ---> %d\n", arg);
}