#include "libservo.h"
#include <stdio.h>
#include "pico/stdlib.h"

/*	Thanks to https://github.com/Thomas-Kleist for the light libservo_pico.a
	that I cannot link to my project so I just copied the sourcefile into 
	libservo.c (+ .h) that I compile in my project

I use a TowerPro micro servo 9g (that I probably endommaged earlier)	
	I found out : 
	- ang 0 seems to be a bit more than 490 (500 for security, ang of almost 5)
	- ang 40 is 1000
	- ang 90 is 1250
	- ang 180 is around 2500
	- nothing changes after 2500
	- there is still a litle step between 2400 and 2500
	What is strange (probably linked to my use) : 
	- below 490 it tries to reach the pos and you hear bzzbzbzzbzb from the motor
	- after 2500 it can't reach anylonger, but it doesnot bzbzbzbzbzzb	
*/

# define SERVOPIN_0 0
# define SERVOPIN 1

int main(void)
{
	const int	low = 700;
	const int	high = 2500;
	const int	test = 2400;

	stdio_init_all();
	setServo(SERVOPIN_0, low);
	setServo(SERVOPIN, low);
	
	while (true)
	{
		for (int current = low; current < high; current += 100)
		{
			setMillis(SERVOPIN, current);
			setMillis(SERVOPIN_0, current);
			if (current == low)
			{
				printf("low pos (%i):\n", current);
				sleep_ms(5000);
			}
			else
				printf("current ms : %i\n", current);
			sleep_ms(3000);
		}
	}
	
	
	/*while (true)
	{
		setMillis(SERVOPIN, low);
		setMillis(SERVOPIN_0, low);
		printf("low pos\n");
		sleep_ms(10000);
		setMillis(SERVOPIN, high);
		setMillis(SERVOPIN_0, high);
		printf("high pos\n");
		sleep_ms(5000);
	}*/
}
