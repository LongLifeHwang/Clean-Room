#include "../clean_room.h"

static void	cleaning(int flag)
{
	all_close();
	digitalWrite(LED, 1);
	digitalWrite(Motor1Right, 1);
	digitalWrite(Motor1Left, 0);
	delay(flag);
	digitalWrite(Motor1Right, 0);
	digitalWrite(LED, 0);
}

//https://blog.naver.com/simjk98/222149165719
static void	door_move(char flag)
{
	if (flag == 'I')
	{
		softPwmWrite(InServo, open);
		while (digitalRead(InRemit) == 0)  //answer : 1
			delay(100);
		printf("entrance open\n");
		delay(100);
		while (digitalRead(InRemit) == 1) //answer : 0
			delay(100);
		delay(100);
		printf("entrance close\n");
		softPwmWrite(InServo, close);
	}
	else if (flag == 'O')
	{
		softPwmWrite(OutServo, open);
		while (digitalRead(OutRemit) == 0) //answer : 1
			delay(100);
		delay(100);
		printf("exit open\n");
		while (digitalRead(OutRemit) == 1) //answer : 0
			delay(100);
		printf("exit close\n");
	}
}

static void	rip_check(int flag)
{
	printf("...air shower setting...\n");
	all_close();
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
		1.way_in open and close
		2.rip check
		3.air shower
		4.way_out open adn close
	*/
	door_move(way_in);
	rip_check(1);
	cleaning(3000);
	door_move(way_out);
	exhaust(3000);
	// dust_check(); //먼지 확인
}