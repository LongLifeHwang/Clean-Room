#include "../clean_room.h"

//https://blog.naver.com/simjk98/222149165719
static void	door_move(char flag)
{
	if (flag == 'I')
	{
		softPwmWrite(InServo, open);
		while (digitalRead(InRemit) == 1)
			delay(100);
		printf("entrance open\n");
		delay(100);
		while (digitalRead(InRemit) == 0)
			delay(100);
        delay(100);
		printf("entrance close\n");
		softPwmWrite(InServo, close);
        softPwmWrite(OutServo, close);
	}
	else if (flag == 'O')
	{
		while (digitalRead(OutRemit) == 1)
			delay(100);
		delay(100);
		printf("exit open\n");
		while (digitalRead(OutRemit) == 0)
			delay(100);
		printf("exit close\n");
		// softPwmWrite(OutServo, close);
	}
}

static void	rip_check(int flag)
{
	printf("...air shower setting...\n");
	while (digitalRead(OutRemit) == 0 || digitalRead(InRemit) == 0)
		delay(100);
	softPwmWrite(OutServo, close);
	softPwmWrite(InServo, close);
	while (flag && digitalRead(InPerson) == 0)
		delay(100);
	printf("air shower starting\n");
    // int i;

    // i = -1;
	// while (flag && digitalRead(InPerson) == 0);
	// printf("...air shower setting...\n");
	// while (digitalRead(InPerson) == 1);
	// while (++i < 20)
	// {
	// 	if (digitalRead(InPerson) == 1)
	// 		break ;
	// 	delay(100);
    // }
	// if (i < 20)
	// {
	// 	printf("move checking!!!\n...restarting...\n");
	// 	rip_check(0);
	// }
	// printf("air shower starting\n");
}

void	iot_main(char way_in, char way_out)
{
	/*
	logic
		1.entrance open and close
		2.rip check
		3.air shower
		4.출구 열기
		5.잠깐 기다리기
		6.나오는 것 감지
		7.출구 열기
		8.초음파로 감지
		9.에어샤워
		10.입구 열기
	*/
	door_move(way_in);
    rip_check(1);
    cleaning(3000);
	door_move(way_out);
	dust_check(); //먼지 확인
}