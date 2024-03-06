#include "../clean_room.h"

void    iot_main(void)
{
    //ultrasonic wave door in
    ultrasonic_wave(1, 29);  //front(1, 29)
    //door open
    door_move(0, 'O');
    //ultrasonic wave clean do it
    ultrasonic_wave(2, 30);  //middle(2, 30)
    //door close
    door_move(o, 'C');
    //pen do it 짝수는 clean room 청소, 홀수는 바람 주기
    pen_move(3);
    

}