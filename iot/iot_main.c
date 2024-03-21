#include "../clean_room.h"

void    iot_main(void)
{
    door_move('I');
    cleaning(5000);
    door_move('O');
}