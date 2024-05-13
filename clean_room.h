#ifndef CLEAN_ROOM_H
# define CLEAN_ROOM_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>

//rasberry pi setting
# include <wiringPi.h>
# include <softPwm.h>

# define CloseOut 5
# define OpenOut 15
# define OpenIn 15
# define CloseIn 1

//https://m.blog.naver.com/kimmy5000/220461603097
//air blower
# define Motor1Right 27
# define Motor1Left 26
# define Motor2Right 29
# define Motor2Left 28

//entrance lock
//https://blog.naver.com/simjk98/222149165719
# define InServo 1
# define InRemit 22

//exit lock
# define OutServo 23
# define OutRemit 25

//ultrasonic sensor
# define trig 4
# define echo 5

//dust sensor
//https://m.blog.naver.com/simjk98/222133748955
# define Dust 3

//LED
# define LED 2

//bluetooth
//https://www.youtube.com/watch?v=D01Apli9qq4&list=PLiqbe2cCqMjUbO_VVxyEHPS55X-gflan8&index=8
//https://chat.openai.com/share/66a11e17-5bcc-4528-9ad2-018081583d22
# define BlueTxd 15
# define BlueRxd 16

//ft_split.c
char	**ft_split(char *str, char c);
//dust_check.c
void	all_close(void);
void	exhaust(int flag);
//iot_main.c
void	iot_main(char way_in, char way_out);
void	cleaning(int left, int right, int flag);

#endif
