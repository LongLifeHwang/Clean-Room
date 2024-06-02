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

static void	data_init(Data *data)
{
	data->status = true;
	data->angle1 = 0.0;
	data->angle2 = 0.0;
	data->motor1 = false;
	data->motor2 = false;
}

static void	parents_process(pid_t child, Data *data)
{
	static int	flag = 0;
	int			status;
	pthread_t	pthread;

	wait(&status);
	if (flag == 0)
	{
		data = malloc(sizeof(Data));
		if (data == 0)
			exit(1);
		gtk_init(NULL, NULL);
		data->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		data->darea = gtk_drawing_area_new();
		gtk_container_add(GTK_CONTAINER(data->window), data->darea);
		flag = 1;
	}
	printf("status : %d\n", status);
	data_init(data);
	pthread_create(&pthread, NULL, &thread_function, data);
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
	data->status = false;
	pthread_join(pthread, NULL);
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
	Data	*data;
	pid_t	child;

	if (argc != 2)
		exit(0);
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
			parents_process(child, data);
	}
	wait(NULL);
	if (data != 0)
		free(data);
	exit (0);
}
