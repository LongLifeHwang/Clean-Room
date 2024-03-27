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

// # define 1 1
// # define 1 0

//https://m.blog.naver.com/kimmy5000/220461603097
//송풍기
# define Motor1Right 26
# define Motor1Left 27
# define Motor2Right 28
# define Motor2Left 29

//https://fishpoint.tistory.com/7140#google_vignette
// 입구 초음파
// # define InTrig 27
// # define InEcho 28
// # define InDoor 29
// 출구 초음파
// # define OutTrig 0 
// # define OutEcho 2
// # define OutDoor 3

//입구 인체 감지 센서
# define InPerson 21

//https://blog.naver.com/simjk98/222149165719
//입구 잠금 장치
# define InServo 18
# define InRemit 25
//출구 잠금 장치
# define OutServo 18 //23
# define OutRemit 22

//https://m.blog.naver.com/simjk98/222133748955
//먼지
# define Dust 23

//블루투스 5v
//https://www.youtube.com/watch?v=D01Apli9qq4&list=PLiqbe2cCqMjUbO_VVxyEHPS55X-gflan8&index=8
//https://chat.openai.com/share/66a11e17-5bcc-4528-9ad2-018081583d22
# define BlueTxd 15
# define BlueRxd 16


//ft_split.c
char	**ft_split(char *str, char c);

//dest_check.c
void    dust_check(void);
void    cleaning(int flag);
//iot_main.c
void    iot_main(void);

#endif