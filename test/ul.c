#include "../clean_room.h"
#define trig 5
#define echo 4

int	main(void)
{
	int	dis;
	long	start;
	long	end;

	wiringPiSetup();
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	while (1)
	{
		digitalWrite(trig, LOW);
		usleep(2);
		digitalWrite(trig, HIGH);
		usleep(20);
		digitalWrite(trig, LOW);
		while (digitalRead(echo) == LOW);
		start = micros();
		while (digitalRead(echo) == HIGH);
		end = micros() - start;
		dis = end / 58;
		printf("distance : %d\n", dis);
		delay(500);
	}
	return (0);
}

