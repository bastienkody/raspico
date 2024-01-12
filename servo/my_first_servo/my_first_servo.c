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

# define SERVOPIN 0

int main(void)
{
	const int	low = 500;
	const int	high = 2500;
	const int	test = 2400;

	setServo(SERVOPIN, low);
	while (true)
	{
		setMillis(SERVOPIN, low);
		sleep_ms(10000);
		setMillis(SERVOPIN, test);
		sleep_ms(10000);
		setMillis(SERVOPIN, high);
		sleep_ms(10000);
	}
}