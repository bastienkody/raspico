#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


/*
Schematics of slideswitch (aka toggle switch) with 3 pins : 
		||
   ------------
	|	 |	 |

Schematics of project:
	https://wokwi.com/projects/386831676154020865

Wiring :
	Left pin to power (5v via vbus/vsys or 3.3v via 3V3 or pico)
	Right pin to any GND
	Middle pin sends output : connect it to a GPIO (I choose the top left 0)

Usage :
	Slide it left : joins left powered and mid pins : power is then sent to gpio
	Slide it right : joins right (grounded) and mid pins : no power is sent

My code : 
	Reads input from slideswitch in pin 0:
		if powered : printf + default led blink once
	minicom requires sudo on my machine (no msg if no sudo merci pour les 25 min de debug)
	"sudo minicom -b 115200 -o -D /dev/ttyACM0"

Pico-sdk hardware_gpio functions :
	gpio_set_dir() : tell if pin scan input or send output
	gpio_put() : send power or none to via an output pin
	gpio_get() : scan power from an input pin
	gpio_pull_up : 
*/

int main(void)
{
	// pin nb for slideswitch input + led25 output
	const uint PIN_SWITCH = 0;
	const uint PIN_LED_25 = PICO_DEFAULT_LED_PIN;

	stdio_init_all();
	// init pin
	gpio_init(PIN_SWITCH);
	gpio_init(PIN_LED_25);
	// make it scan input (vs GPIO_OUT to send outputs)
	gpio_set_dir(PIN_SWITCH, GPIO_IN);
	gpio_set_dir(PIN_LED_25, GPIO_OUT);
	// turn it on ? more info needed
	gpio_pull_up(PIN_SWITCH);

	while (1)
	{
		if (gpio_get(PIN_SWITCH))
		{
			printf("FLAG\n");
			gpio_put(PIN_LED_25, 1);
			sleep_ms(500);
			gpio_put(PIN_LED_25, 0);
		}
		sleep_ms(250);
	}
}
