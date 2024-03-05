#include "../clean_room.h"

# define FLAG 10

void    ultrasonic_wave(int tringpin, int echopin)
{
    int     distance;
    int     pulse;
    long    start;
    long    travel;

    pinMode(tringpin, OUTPUT);
    pinMode(echopin, INPUT);
    while (1)
    {
        digitalWrite(tringpin, LOW);
        usleep(2);
        digitalWrite(tringpin, HIGH);
        usleep(20);
        digitalWrite(tringpin, LOW);
        while (dightalRead(echopin) == LOW);
        start = micros();
        while (dightalRead(echopin) == HIGH);
        travel = micros() - start;
        distance = travel / 58;
        // printf("distance : %d \n", distance);
        if (distance < FLAG)
            return ;
    }
}
