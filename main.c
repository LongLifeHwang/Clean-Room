//Programing
//python, c

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

	wait(&status);
	printf("%d\n",status);
	delay(2000);
	if (status == 0)
		iot_main();
	else
	{
		printf("yolo error\n");
		exit(1);
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
		// dust_check();
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
static void	child_process(char *argv[], char *envp[])
{
	char	**command;

	command = ft_split(argv[1], ' ');
	if (command == NULL)
		exit (1);
	execve("/usr/bin/python3", command, envp);
}

static void	 parents_process(void)
{
	int	 status;

	wait(&status);
	printf("%d\n",status);
	delay(2000);
	if (status == 0)
		iot_main();
	else
	{
		printf("yolo error\n");
		exit(1);
	}
}

static void	init(void)
{
	if (wiringPiSetup() == -1)
	{
		printf("GPIO error\n");
		exit(1);
	}
	//송풍기
	pinMode(Motor1Right, OUTPUT);
	pinMode(Motor1Left, OUTPUT);
	pinMode(Motor2Right, OUTPUT);
	pinMode(Motor2Left, OUTPUT);
	//입구 인체감지 센서

	//입구 잠금 장치
	pinMode(InRemit, INPUT);
	pullUpDnControl(InRemit, PUD_DOWN);
	pinMode(InServo, OUTPUT);
	softPwmCreate(InServo, 0, 200);
	softPwmWrite(InServo, 5);
	//출구 잠금 장치
	pinMode(OutRemit, INPUT);
	pullUpDnControl(InRemit, PUD_DOWN);
	// pinMode(OutServo, PWM_OUTPUT);
	// softPwmCreate(OutServo, 0, 200);
	// softPwmWrite(OutServo, 5); //-90
	//인체 감지 센서
	pinMode(InPerson, INPUT);
	//먼지
	// pinMode(Dust, INPUT);
	//블루투스
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t   child;

	if (argc != 2)
		exit(0);
	init();
	while (1)
	{
		// dust_check();
		child = fork();  //python3 yolo
		if (child < 0)
		{
			printf("fork error\n");
			exit(1);
		}
		else if (child == 0) // child
			child_process(argv, envp);
		else  //parents
			parents_process();
	}
	exit (0);
}
