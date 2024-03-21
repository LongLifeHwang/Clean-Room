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

# define HIGH 1
# define LOW 0

//https://m.blog.naver.com/kimmy5000/220461603097
//송풍기
# define MotorRight 1
# define MotorLeft 1

//https://fishpoint.tistory.com/7140#google_vignette
// 입구 초음파
// # define InTrig 1
// # define InEcho 1
# define InDoor 1
// 출구 초음파
// # define OutTrig 1
// # define OutEcho 1
# define OutDoor 1

//https://blog.naver.com/simjk98/222149165719
//입구 잠금 장치
# define InServo 1
//출구 잠금 장치
# define OutServo 1

//https://m.blog.naver.com/simjk98/222133748955
//먼지
# define Dust 1

//ft_split.c
char	**ft_split(char *str, char c);

//dest_check.c
void    dust_check(void);
void    cleaning(int flag);
//iot_main.c
void    iot_main(void);

void    ultrasonic_wave(int tringpin, int echopin);
void    door_move(char flag);
void    pen_move(int flag);

#endif