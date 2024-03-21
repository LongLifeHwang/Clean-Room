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

//https://m.blog.naver.com/kimmy5000/220461603097
//송풍기
# define MotorRight 1
# define MotorLeft 1

//https://fishpoint.tistory.com/7140#google_vignette
// 입구 초음파
# define InTrig 1
# define InEcho 1
// 출구 초음파
# define OutTrig 1
# define OutEcho 1

//https://blog.naver.com/simjk98/222149165719
//입구 잠금 장치
# define InServo 1
//출구 잠금 장치
# define OutServo 1

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