#include "../clean_room.h"

void	all_close(void)
{
	while (digitalRead(OutRemit) == 1 || digitalRead(InRemit) == 1) //answer : 0
		delay(100);
	softPwmWrite(OutServo, close);
	softPwmWrite(InServo, close);
}

//https://m.blog.naver.com/simjk98/222133748955
void	dust_check(void)
{
	unsigned int	pre;
	unsigned int	cur;
	unsigned long	flag;
	int				count;

	all_close();
	pre = millis();
	count = 0;
	while (1)
	{
		cur = millis();
		if (digitalRead(Dust))
			count++;
		if (cur - pre > 5000)
		{
			if (count > 20) //먼지 체크
				cleaning(Motor2Left, Motor2Right, 3000);
			break ;
		}
		delay(20);
	}
    softPwmWrite(OutServo, Open);
}
