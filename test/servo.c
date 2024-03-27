# include <wiringPi.h>
# include <softPwm.h>

# define InServo 18

int main(void)
{
    wiringPiSetupGpio();
    pinMode(InServo, OUTPUT);
    softPwmCreate(InServo, 0, 200);
    while (1)
    {
        softPwmWrite(InServo, 10);
        delay(500);
        softPwmWrite(InServo, 15);
        delay(500);
        softPwmWrite(InServo, 20);
        delay(500);
    }
}