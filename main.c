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

static void	parents_process(void)
{
	int	status;

    while (1)
    {
        waitpid(-1, &status, WNOHANG);
        if (WIFEXITED(status))
        {
            iot_main('I', 'O');
            break ;
        }
        if (digitalRead(OutRemit) == 0)
        {
            iot_main('O', 'I');
			wait(&status);
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
	softPwmWrite(InServo, close);
	//exit lock
	pinMode(OutRemit, INPUT);
	pullUpDnControl(InRemit, PUD_DOWN);
	pinMode(OutServo, OUTPUT);
	softPwmCreate(OutServo, 0, 200);
	softPwmWrite(OutServo, close);
	//clean_room rip sensor
	pinMode(InPerson, INPUT);
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
	init();
	while (1)
	{
		child = fork();
		if (child < 0)
		{
			printf("fork error\n");
			exit(1);
		}
		else if (child == 0)
			child_process(argv, envp);
		else
			parents_process();
	}
	exit (0);
}
