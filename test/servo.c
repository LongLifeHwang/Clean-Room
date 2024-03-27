#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

# define InServo 1

int main(void)
{
    if(wiringPiSetup()==-1)
        return 1;

    softPwmCreate(InServo, 0, 200);
    while (1)
    {
        softPwmWrite(InServo, 10);
        delay(500);
        softPwmWrite(InServo, 15);
        delay(500);
        softPwmWrite(InServo, 20);
        delay(500);
        printf("servo\n");
    }
}