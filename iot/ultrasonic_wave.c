#include "../clean_room.h"

void    ultrasonic_wave(int tring, int echo)
{
    int     distance;
    int     pulse;
    long    start;
    long    travel;
    int     flag;

    while (1)
    {
        digitalWrite(tring, LOW);
        usleep(2);
        digitalWrite(tring, HIGH);
        usleep(20);
        digitalWrite(tringpin, LOW);
        while (dightalRead(echopin) == LOW);
        start = micros();
        while (dightalRead(echopin) == HIGH);
        travel = micros() - start;
        distance = travel / 58;
        // printf("distance : %dcm \n", distance);
        if (distance < 2) //길목 크기 
            return ;
    }
}
