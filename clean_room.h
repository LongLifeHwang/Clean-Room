#ifndef CLEAN_ROOM_H
# define CLEAN_ROOM_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

//rasberry pi setting
# include <wiringPi.h>

char	**ft_split(char *str, char c);
void    iot_main(void);
void    ultrasonic_wave(int tringpin, int echopin);
void    door_move(int flag);

#endif