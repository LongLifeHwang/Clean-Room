#include "../clean_room.h"

void    ultrasonic_wave(int trig, int echo)
{
    long    distance;
    long    start;
    long    travel;

    while (1)
    {
        digitalWrite(trig, LOW);
        usleep(2);
        digitalWrite(trig, HIGH);
        usleep(20);
        digitalWrite(trig, LOW);
        while (dightalRead(echo) == LOW);
        start = micros();
        while (dightalRead(echo) == HIGH);
        travel = micros() - start;
        distance = travel / 58;
        // printf("distance : %dcm \n", distance);
        if (distance < 5) //길목 크기 
            return ;
    }
}
