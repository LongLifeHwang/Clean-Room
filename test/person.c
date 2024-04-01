#include "../clean_room.h"

int	main(int argc, char *argv[])
{
	if (wiringPiSetup() == -1)
		return (-1);
	while (1)
	{
		printf("digitalRead(21) : %d\n", digitalRead(21));
		delay(100);
	}
	return (0);
}
