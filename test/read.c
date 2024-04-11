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
        printf("digtiralRead(LED) : %d\n", digtiralRead(LED));
        delay(500);
    }
    return (0);
}