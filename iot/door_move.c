#include "../clean_room.h"

//https://blog.naver.com/simjk98/222149165719

void    door_move(char flag)
{
    if (c == 'I')
    {
        softPwmWrite(InServo, 24); //90 open
        while (digitalRead(InDoor) == LOW);
        while (digitalRead(InDoor) == HIGH);
        softPwmWrite(InServo, 5); //-90 close
    }
    else if (C == 'O')
    {
        softPwmWrite(OutServo, 24); //90 open
        while (digitalRead(OutDoor) == LOW);
        while (digitalRead(OutDoor) == HIGH);
        softPwmWrite(OutServo, 5); //-90 open
    }
}