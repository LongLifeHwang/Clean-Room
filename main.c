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

//ai yolo v5
static void	child_process(char *argv[], char *envp[])
{
	char	**command;
	int		fd;

	fd = open("log", O_WRONLY, O_CREAT, O_TRUNC, 0777);
	dup2(fd, 1);
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

	fd = open("log", O_RDONLY);
	while (1)
	{
		printf("WIFEXITED(status) : %d\n", WIFEXITED(status));
		ret = read(fd, buff, 20);
		buff[ret] = '\0';
		if (buff[0] == 'O')
		{
			close(fd);
			softPwmWrite(OutServo, close);
			iot_main('I', 'O');
			fd = open("log", O_WRONLY, O_TRUNC);
			close(fd);
		}
		if (digitalRead(OutRemit) == 1) //answer : 1
		{
			close(fd);
			iot_main('O', 'I');
			fd = open("log", O_WRONLY, O_TRUNC);
			close(fd);
		}
	}
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
	//dust sensor
	pinMode(Dust, INPUT);
	//LED
	pinMode(LED, OUTPUT);
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
		softPwmWrite(OutServo, Open);
		softPwmWrite(InServo, Close);
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
	exit (0);
}
