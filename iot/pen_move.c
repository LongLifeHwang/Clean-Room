#include "../clean_room.h"

static void led_control(int flag)
{
    if (flag != 1 && flag != 0)
        return ;
    digitalWrite(LED, flag);
}

void    pen_move(int flag)
{
    if (flag < 0)
        return ;
    if (flag % 2 == 0)
    {
        //led on
        led_control(1);
        digitalWrite(CLEANPEN1, 1);
        digitalWrite(CLEANPEN2, 1);
        sleep(flag);
        digitalWrite(CLEANPEN1, 0);
        digitalWrite(CLEANPEN2, 0);
        //led off
        led_control(0);
    }
    else if (flag % 2 == 1)
    {
        //led on
        led_control(1);
        digitalWrite(PENDO1, 1);
        digitalWrite(PENDO2, 1);
        digitalWrite(PENDO3, 1);
        digitalWrite(PENDO4, 1);
        digitalWrite(PENDO5, 1);
        digitalWrite(PENDO6, 1);
        digitalWrite(PENDO7, 1);
        digitalWrite(PENDO8, 1);
        digitalWrite(PENDO9, 1);
        digitalWrite(PENDO10, 1);
        sleep(3);
        digitalWrite(PENDO1, 0);
        digitalWrite(PENDO2, 0);
        digitalWrite(PENDO3, 0);
        digitalWrite(PENDO4, 0);
        digitalWrite(PENDO5, 0);
        digitalWrite(PENDO6, 0);
        digitalWrite(PENDO7, 0);
        digitalWrite(PENDO8, 0);
        digitalWrite(PENDO9, 0);
        digitalWrite(PENDO10, 0);
        //led off
        led_control(0);
    }
}