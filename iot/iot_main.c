#include "../clean_room.h"

void    iot_main(void)
{
    //ultrasonic wave door in
    ultrasonic_wave(1, 29);
    //door open
    door_move(0);
    //ultrasonic wave clean do it
    ultrasonic_wave(1, 29);
    //door close
    door_move(1);
    //pen do it
    // pen_move(0);

}