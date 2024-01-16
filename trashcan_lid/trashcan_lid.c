#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/*	checker si le keyword inline en c11 est pertinent	*/

/*	TIME	*/
#define MIN_TIME 4000
#define MIN_IN_BETWEEN 450

/*	PINs	*/
#define P_SWITCH 0
#define P_SERVO 1
#define P_PIR 2
#define P_LED25 PICO_DEFAULT_LED_PIN


void	blink_led(uint led_pin, uint loop_nb, uint one_lap_time_ms, char *msg)
{
	if (one_lap_time_ms < 40)
		one_lap_time_ms = 40;
	for (; loop_nb > 0, --loop_nb)
	{
		if (msg)
			printf("%s\n", msg);
		gpio_put(led_pin, true);
		sleep_ms(one_lap_time_ms / 2);
		gpio_put(P_LED25, false);
		sleep_ms(one_lap_time_ms / 2);
	}
}

void	calibrate_pir(uint sec)
{
	printf("Calibrating pir sensor for %u sec\n", sec);
	for (; sec > 0; sec--)
		blink_led(P_LED25, 50, 1000, "Calibrating pir ..")
}


void	setup(void)
{
	stdio_init_all();

	// slide switch as input
	gpio_init(P_SWITCH);
	gpio_set_dir(P_SWITCH, GPIO_IN);
	// servo as output
	gpio_init(P_SERVO);
	gpio_set_dir(PIN_SERVO, GPIO_OUT);
	// onbaord led to debug
	gpio_init(P_LED25);
	gpio_set_dir(P_LED25, GPIO_OUT);
	// infra sensor as input
	gpio_init(P_PIR);
	gpio_set_dir(PIN_PIR, GPIO_IN);
	calibrate_pir(50);
	//blink to show end of setup
	blink_led(P_LED25, 10, 100, "Setup done!");
}

//	if power goes through switch : not locked
inline bool	is_locked(void)
{
	return (!gpio_get(P_SWITCH));
}

//	if power from pir : motion detected
inline bool	is_motion(void)
{
	return (gpio_get(P_PIR))
}

int main(void)
{
	bool	is_opened = false;

	setup();

	while (true)
	{
		if (!is_opened && is_motion() && !is_locked())
		{
			printf("Motion detected and switch opened : trashcan lid is about to open\n");
			//open servo a 100-115degrees
			is_opened = true;
			sleep_ms(MIN_TIME);
		}
		if (is_opened && !is_locked() && !is_motion())
		{
			printf("lid opened, switch opened and no motion detected : lid about to close\n");
			// close servo at 5
			is_opened = false;
		}
		sleep_ms(MIN_IN_BETWEEN);
	}
}