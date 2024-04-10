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

	command = ft_split(argv[1], ' ');
	if (command == NULL)
		exit (1);
	execve("/usr/bin/python3", command, envp);
}

static void	parents_process(pid_t child)
{
	int	status;

	while (1)
	{
		waitpid(-1, &status, WNOHANG);
		printf("WIFEXITED(status) : %d\n", WIFEXITED(status));
		if (WIFEXITED(status))
		{
			softPwmWrite(OutServo, close);
			iot_main('I', 'O');
			break ;
		}
		if (digitalRead(OutRemit) == 1) //answer : 1
		{
			iot_main('O', 'I');
			kill(child, SIGKILL);
			break ;
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
		softPwmWrite(OutServo, open);
		softPwmWrite(InServo, close);
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
