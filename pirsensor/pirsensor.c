#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define PIR_PIN 0
#define LED25_PIN PICO_DEFAULT_LED_PIN

void	calibrate_pir_sensor(uint sec)
{
	for (; sec > 0; sec--)
	{
		printf("Calibrating pir sensor .. (remaining %u)\n", sec);
		gpio_put(LED25_PIN, 1);
		sleep_ms(500);
		gpio_put(LED25_PIN, 0);
		sleep_ms(500);
	}
}

int main(void)
{
	stdio_init_all();

	gpio_init(PIR_PIN);
	gpio_init(LED25_PIN); 

	gpio_set_dir(PIR_PIN, GPIO_IN);
	gpio_set_dir(LED25_PIN, GPIO_OUT);

	calibrate_pir_sensor(5);

	while (1)
	{
		int	motio_nb = 0;
		while (gpio_get(PIR_PIN))
		{
			printf("Motion detected (%i)\n", ++motio_nb);
			gpio_put(LED25_PIN, 1);
			sleep_ms(500);
			gpio_put(LED25_PIN, 0);
		}
		sleep_ms(250);
	}
}
