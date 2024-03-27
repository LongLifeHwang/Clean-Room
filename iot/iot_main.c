#include "../clean_room.h"

//https://blog.naver.com/simjk98/222149165719
static void door_move(char flag)
{
    if (flag == 'I')
    {
        softPwmWrite(InServo, 24); //90 open
        printf("here1\n");
        while (digitalRead(InRemit) == LOW)
        {
            delay(100);
        }
        printf("here1\n");
        delay(100);
        while (digitalRead(InRemit) == HIGH)
        {
            delay(100);
        }
        softPwmWrite(InServo, 5); //-90 close
    }
    else if (flag == 'O')
    {
        softPwmWrite(OutServo, 24); //90 open
        while (digitalRead(OutRemit) == LOW)
        {
            delay(100);
        }
        delay(100);
        while (digitalRead(OutRemit) == HIGH)
        {
            delay(100);
        }
        softPwmWrite(OutServo, 5); //-90 open
    }
}

static void ultrasonic_wave(int trig, int echo)
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
        while (digitalRead(echo) == LOW);
        start = micros();
        while (digitalRead(echo) == HIGH);
        travel = micros() - start;
        distance = travel / 58;
        // printf("distance : %dcm \n", distance);
        if (distance < 5) //길목 크기 
            return ;
    }
}

void    iot_main(void)
{
    /*
    순서
        1.입구 열기
        2.초음파로 감지
        3.에어 샤워
        4.출구 열기
        5.잠깐 기다리기
        6.나오는 것 감지
        7.출구 열기
        8.초음파로 감지
        9.에어샤워
        10.입구 열기
    */
    printf("here\n");
    door_move('I');
    printf("here1\n");
    // ultrasonic_wave(InTrig, InEcho);
    // cleaning(5000);
    door_move('O');
    printf("here2\n");
    // dust_check(); //먼지 확인
    // ultrasonic_wave(OutTrig, OutEcho);
    door_move('O');
    printf("here3\n");
    // ultrasonic_wave(InTrig, InEcho);
    // cleaning(5000);
    door_move('I');
    printf("here4\n");
}
