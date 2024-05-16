# include <wiringPi.h>
# include <stdio.h>
# include <sys/wait.h>

# define LED 29 

int main(void)
{
    int flag;

    if (wiringPiSetup() == -1)
	{
		printf("GPIO error\n");
        return (0);
	}
    pinMode(LED, OUTPUT);
    flag = 0;
    while (flag++ < 30)
    {
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        delay(1000);
    }
    return (0);
}
