#include "../clean_room.h"

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
    door_move('I');
    ultrasonic_wave(InTrig, InEcho);
    cleaning(5000);
    door_move('O');
    delay(2000); //초음파 센서 기다리기
    ultrasonic_wave(OutTrig, OutEcho);
    door_move('O');
    ultrasonic_wave(InTrig, InEcho);
    cleaning(5000);
    door_move('I');
}
