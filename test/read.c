# include <wiringPi.h>
# include <stdio.h>
# include <sys/wait.h>

# define LED 0

int main(void)
{
    int flag;

    if (wiringPiSetup() == -1)
	{
		printf("GPIO error\n");
        return (0);
	}
    pinMode(LED, INPUT);
    flag = 0;
    while (flag++ < 10)
    {
        printf("digitalRead(LED) : %d\n", digitalRead(LED));
        delay(100);
    }
    return (0);
}