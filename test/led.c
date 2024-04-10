# include <wiringPi.h>
# include <stdio.h>
# include <sys/wait.h>

# define LED 0

int main(void)
{
    if (wiringPiSetup() == -1)
	{
		printf("GPIO error\n");
        return (0);
	}
    pinMode(LED, OUTPUT);
    while (1)
    {
        digitalWrite(LED, HIGH);
        sleep(1);
        digitalWrite(LED, LOW);
        sleep(1);
    }
}