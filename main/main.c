#include <unistd.h>
#include <stdio.h>
#include "esp_wifi.h"

void	app_main(void)
{
	while(1) {
		write(1, "VampetaOS\n", 10);
		sleep(1);
	}
}