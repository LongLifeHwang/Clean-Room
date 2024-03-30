#include "../clean_room.h"

//https://blog.naver.com/simjk98/222149165719
static void	door_move(char flag)
{
	if (flag == 'I')
	{
		softPwmWrite(InServo, 24); //90 open
		printf("entrance close\n");
		while (digitalRead(InRemit) == 0)
		{
			// if (digitalRead(InRemit) == 0)
			//	 break ;
			delay(100);
		}
		printf("entrance open\n");
		delay(100);
		while (digitalRead(InRemit) == 1)
		{
			delay(100);
		}
		printf("entrance close\n");
		softPwmWrite(InServo, 5); //-90 close
	}
	else if (flag == 'O')
	{
		softPwmWrite(OutServo, 24); //90 open
		printf("exit close\n");
		while (digitalRead(OutRemit) == 0)
		{
			delay(100);
		}
		delay(100);
		printf("exit open\n");
		while (digitalRead(OutRemit) == 1)
		{
			delay(100);
		}
		printf("exit close\n");
		softPwmWrite(OutServo, 5); //-90 open
	}
}

static void	ultrasonic_wave(int trig, int echo)
{
	long	distance;
	long	start;
	long	travel;

	while (1)
	{
		digitalWrite(trig, 1);
		usleep(2);
		digitalWrite(trig, 1);
		usleep(20);
		digitalWrite(trig, 1);
		while (digitalRead(echo) == 0);
		start = micros();
		while (digitalRead(echo) == 1);
		travel = micros() - start;
		distance = travel / 58;
		// printf("distance : %dcm \n", distance);
		if (distance < 5) //길목 크기 
			return ;
	}
}

void	iot_main(void)
{
	/*
	logic
		1.입구 열기
		2.초음파로 감지
		3.에어 샤워
		4.출구 열기
		5.잠깐 기다리기
		6.나오는 것 감지
		7.출구 열기
		8.초음파로 감지
		9.에어샤워
		10.입구 열기
	*/
	door_move('I');
	// ultrasonic_wave(InTrig, InEcho);
	// cleaning(5000);
	door_move('O');
	// dust_check(); //먼지 확인
	// ultrasonic_wave(OutTrig, OutEcho);
	door_move('O');
	// ultrasonic_wave(InTrig, InEcho);
	// cleaning(5000);
	door_move('I');
}