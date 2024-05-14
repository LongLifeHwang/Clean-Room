//install
/*
sudo apt-get install wringpi
compile : -lwiringpi
*/

//sensor position
/*
front : camera(yolo v5)
back : ultrasonic wave
in : cooler(8)
*/

#include "./clean_room.h"
#include <wiringPi.h>
//ai yolo v5
static void	child_process(char *argv[], char *envp[])
{
	char	**command;

	printf("here\n");
	pinMode(InServo, INPUT);
	pinMode(OutServo, INPUT);
	command = ft_split(argv[1], ' ');
	if (command == NULL)
		exit (1);
	execve("/usr/bin/python3", command, envp);
}

static void	parents_process(pid_t child)
{
	char	buff[20];
	int		fd;
	int		ret;
	int		status;

	wait(&status);
	printf("status : %d\n", status);
	pinMode(InServo, OUTPUT);
	softPwmCreate(InServo, 0, 200);
	pinMode(OutServo, OUTPUT);
	softPwmCreate(OutServo, 0, 200);
	if (status == 0)
	{
		softPwmWrite(OutServo, CloseOut);
		delay(200);
		iot_main('I', 'O');
	}
	else
		iot_main('O', 'I');
	//while (1)
	//{
	//	fd = open("log", O_RDONLY);
	//	ret = read(fd, buff, 20);
	//	if (ret > 0)
	//	{
	//		printf("success here\n");
	//		close(fd);
	//		break ;
	//		softPwmWrite(OutServo, Close);
	//		iot_main('I', 'O');
	//		fd = open("log", O_WRONLY || O_TRUNC);
	//		close(fd);
	//	}
	//	if (digitalRead(OutRemit) == 1) //answer : 1
	//	{
	//		close(fd);
	//		iot_main('O', 'I');
	//		fd = open("log", O_WRONLY || O_TRUNC);
	//		close(fd);
	//	}
	//	if (ret <= 0 && digitalRead(OutRemit) == 0)
	//		close(fd);
	//}
}

static void	init(void)
{
	if (wiringPiSetup() == -1)
	{
		printf("GPIO error\n");
		exit(1);
	}
	//air blower
	pinMode(Motor1Right, OUTPUT);
	pinMode(Motor1Left, OUTPUT);
	pinMode(Motor2Right, OUTPUT);
	pinMode(Motor2Left, OUTPUT);
	//entrance lock
	pinMode(InRemit, INPUT);
	pullUpDnControl(InRemit, PUD_DOWN);
	pinMode(InServo, OUTPUT);
	softPwmCreate(InServo, 0, 200);
	//exit lock
	pinMode(OutRemit, INPUT);
	pullUpDnControl(InRemit, PUD_DOWN);
	pinMode(OutServo, OUTPUT);
	softPwmCreate(OutServo, 0, 200);
	//clean_room rip sensor
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	//LED
	pinMode(LED, OUTPUT);
	delay(200);
	//bluetooth
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	child;

	if (argc != 2)
		exit(0);
	// delay(10000);  //starting roading
	init();
	while (1)
	{
		softPwmWrite(InServo, CloseIn);
		softPwmWrite(OutServo, OpenOut);
		delay(200);
		child = fork();
		if (child < 0)
		{
			printf("fork error\n");
			exit(1);
		}
		else if (child == 0)
			child_process(argv, envp);
		else
			parents_process(child);
	}
	wait(NULL);
	exit (0);
}
