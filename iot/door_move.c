#include "../clean_room.h"

//https://blog.naver.com/simjk98/222149165719

void    door_move(int servor1, int servo2, char c)
{
    if (c == 'O')
    {
        softPwmWrite(servo1, 10);
        softPwmWrite(servo2, 10);
        printf("%d open\n", flag);
    }
    else if (C == 'C')
    {
        softPwmWrite(servo1, 30);
        softPwmWrite(servo2, 30);
        printf("%d close\n", flag);
    }
}