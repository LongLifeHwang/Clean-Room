#include "../clean_room.h"

void	cleaning(int left, int right, int flag)
{
	all_close();
	digitalWrite(LED, 1);
	digitalWrite(left, 1);
	digitalWrite(right, 0);
	delay(flag);
	digitalWrite(left, 0);
	digitalWrite(LED, 0);
}

//https://blog.naver.com/simjk98/222149165719
static void	door_move(char flag)
{
	if (flag == 'I')
	{
		softPwmWrite(InServo, Open);
		// delay(200);
		//digitalWrite(InServo, 0);
		while (digitalRead(InRemit) == 0)  //answer : 1
			delay(100);
		printf("entrance open\n");
		// delay(100);
		while (digitalRead(InRemit) == 1) //answer : 0
			delay(100);
		delay(100);
		printf("entrance close\n");
		softPwmWrite(InServo, Close);
	}
	else if (flag == 'O')
	{
		softPwmWrite(OutServo, Open);
		//delay(200);
		while (digitalRead(OutRemit) == 0) //answer : 1
			delay(100);
		//delay(100);
		printf("exit open\n");
		while (digitalRead(OutRemit) == 1) //answer : 0
			delay(100);
		printf("exit close\n");
	}
}

static void	ultrasonic_check(void)
{
	int		dis;
	long	start;
	long	end;
	int		count;

	printf("here\n");
	count = 0;
	while (1)
	{
		digitalWrite(trig, 1);
		usleep(20);
		digitalWrite(trig, 0);
		printf("begin\n");
		while (digitalRead(echo) == 0);
		start = micros();
		while (digitalRead(echo) == 1);
		end = micros() - start;
		dis = end / 58;
		printf("distance : %dcm\n", dis);
		//ultrasonic_up(210mm)
		// if (dis < 10)
		// 	break ;
		//ultrasonic_width(75mm) 
		if (dis < 10)
			count++;
		else
			count = 0;
		if (count > 4)
			break ;
		delay(100);
	}
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
	printf("here2\n");
	ultrasonic_check();
	cleaning(Motor2Left, Motor2Right, 3000);
	door_move(way_out);
	cleaning(Motor1Left, Motor1Right, 3000);
	// dust_check(); 
}
