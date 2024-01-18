#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "libservo.h"

/*	Keeps opened time	*/
#define MIN_TIME 5000
/*	Time to wait to reopen after closure	*/
#define MIN_IN_BETWEEN 450

/*	Pin numbers	*/
#define P_SWITCH 3
#define P_SERVO_1 0
#define P_SERVO_2 1
#define P_PIR 2
#define P_LED25 PICO_DEFAULT_LED_PIN

/*	Servo pos	*/
#define SERVO_CLOSED 700
#define SERVO_OPENED 2500


void	blink_led(uint led_pin, uint loop_nb, uint one_lap_time_ms, char *msg)
{
	if (one_lap_time_ms < 40)
		one_lap_time_ms = 40;
	for (; loop_nb > 0; --loop_nb)
	{
		if (msg)
			printf("%s\n", msg);
		gpio_put(led_pin, true);
		sleep_ms(one_lap_time_ms / 2);
		gpio_put(led_pin, false);
		sleep_ms(one_lap_time_ms / 2);
	}
}

void	calibrate_pir(uint sec)
{
	printf("Calibrating pir sensor for %u sec\n", sec);
	blink_led(P_LED25, 50, 1000, "Calibrating pir ..");
}


void	setup(void)
{
	stdio_init_all();
	// servos as output
	setServo(P_SERVO_1, SERVO_CLOSED);
	setServo(P_SERVO_2, SERVO_CLOSED);
	// onbaord led to debug
	gpio_init(P_LED25);
	gpio_set_dir(P_LED25, GPIO_OUT);
	// slide switch as input
	gpio_init(P_SWITCH);
	gpio_set_dir(P_SWITCH, GPIO_IN);
	// infra sensor as input
	gpio_init(P_PIR);
	gpio_set_dir(P_PIR, GPIO_IN);
	calibrate_pir(50);
	//blink to show end of setup
	blink_led(P_LED25, 10, 100, "Setup done!");
}

//	if power goes through switch : not locked
bool	is_locked(void)
{
	return (!gpio_get(P_SWITCH));
}

//	if power from pir : motion detected
bool	is_motion(void)
{
	return (gpio_get(P_PIR));
}

int main(void)
{
	bool	is_opened = false;

	setup();
	while (true)
	{
		if (!is_opened && is_motion() && !is_locked())
		{
			printf("lid open\n");
			setMillis(P_SERVO_1, SERVO_OPENED);
			setMillis(P_SERVO_2, SERVO_OPENED);
			is_opened = true;
			sleep_ms(MIN_TIME);
		}
		if (is_opened && !is_locked() && !is_motion())
		{
			printf("lid close\n");
			setMillis(P_SERVO_1, SERVO_CLOSED);
			setMillis(P_SERVO_2, SERVO_CLOSED);
			is_opened = false;
			sleep_ms(MIN_IN_BETWEEN);
		}
	}
}
