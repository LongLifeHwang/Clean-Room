#include "../clean_room.h"

void    cleaning(int flag)
{
    digitalWrite(MotorRight, HIGH);
    digitalWrite(MotorLeft, LOW);
    delay(flag); //3초
    digitalWrite(MotorRight, LOW);
}

//https://m.blog.naver.com/simjk98/222133748955
void    dust_check(void)
{
    unsigned int    pre;
    unsigned int    cur;
    int             count;
    int             flag;

    cleaning();
    pre = millis();
    count = 0;
    flag = 5000;
    while (1)
    {
        cur = millis();
        if (digitalRead(Dust))
            count++;
        if (cur - pre > flag)
        {
            if (count > 20) //먼지 체크
                cleaning(3000);
            break ;
        }
        delay(20);
    }
}
