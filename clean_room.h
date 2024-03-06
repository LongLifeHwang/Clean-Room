#ifndef CLEAN_ROOM_H
# define CLEAN_ROOM_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

//rasberry pi setting
# include <wiringPi.h>
# include <softPwm.h>

# define CLEANPEN1 1
# define CLEANPEN2 1
# define PENDO1 1
# define PENDO2 1
# define PENDO3 1
# define PENDO4 1
# define PENDO5 1
# define PENDO6 1
# define PENDO7 1
# define PENDO8 1
# define PENDO9 1
# define PENDO10 1
# define SERVO1 1
# define SERVO2 1
# define SERVO3 1
# define SERVO4 1
# define LED 1
# define FLAG 10

char	**ft_split(char *str, char c);
void    iot_main(void);
void    ultrasonic_wave(int tringpin, int echopin);
void    door_move(int flag);
void    pen_move(int flag);

#endif