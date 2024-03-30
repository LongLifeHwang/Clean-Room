#include "../clean_room.h"

void	cleaning(int flag)
{
	digitalWrite(LED, 1);
	digitalWrite(Motor1Right, 1);
	digitalWrite(Motor1Left, 0);
	digitalWrite(Motor2Right, 1);
	digitalWrite(Motor2Left, 0);
	delay(flag); //3초
	digitalWrite(Motor1Right, 0);
	digitalWrite(Motor2Right, 0);
	digitalWrite(LED, 0);
}

//https://m.blog.naver.com/simjk98/222133748955
void	dust_check(void)
{
	unsigned int	pre;
	unsigned int	cur;
	unsigned long	flag;
	int				count;

	cleaning(5000);
	pre = millis();
	count = 0;
	flag = 5000;
	while (1)
	{
		cur = millis();
		if (digitalRead(Dust))
			count++;
		if (cur - pre > flag)
		{
			if (count > 20) //먼지 체크
				cleaning(3000);
			break ;
		}
		delay(20);
	}
}
