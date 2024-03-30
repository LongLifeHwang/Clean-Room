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

# define close 5
# define open 24

//https://m.blog.naver.com/kimmy5000/220461603097
//air blower
# define Motor1Right 26
# define Motor1Left 27
# define Motor2Right 28
# define Motor2Left 29

//entrance lock
//https://blog.naver.com/simjk98/222149165719
# define InServo 1
# define InRemit 22

//exit lock
# define OutServo 23
# define OutRemit 25

//clean_room rip sensor
# define InPerson 21

//dust sensor
//https://m.blog.naver.com/simjk98/222133748955
# define Dust 23

//LED
# define LED 6

//bluetooth
//https://www.youtube.com/watch?v=D01Apli9qq4&list=PLiqbe2cCqMjUbO_VVxyEHPS55X-gflan8&index=8
//https://chat.openai.com/share/66a11e17-5bcc-4528-9ad2-018081583d22
# define BlueTxd 15
# define BlueRxd 16


//ft_split.c
char	**ft_split(char *str, char c);
//dest_check.c
void	all_close(void);
void	dust_check(void);
void	exhaust(int flag);
//iot_main.c
void	iot_main(void);

#endif
