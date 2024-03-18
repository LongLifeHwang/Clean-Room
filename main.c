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

#include "clean_room.h"

//ai yolo v5
static void    child_process(char *argv[], char *envp[])
{
    char    **command;

    command = ft_split(argv[1], ' ');
    if (command == NULL)
        exit (1);
    execve("/usr/bin/python3", command, envp);
}

static void     parents_process(void)
{
    int     status;

    wait(&status);
    printf("%d\n",status);
    if (status == 0)
        iot_main();
    else
    {
        printf("error\n");
        exit(1);
    }
}

static void init(void)
{
    if (wiringPiSetup() == -1)
    {
        printf("GPIO error\n");
        exit(1);
    }
    pinMode(CLEANPEN1, OUTPUT);
    pinMode(CLEANPEN2, OUTPUT);
    pinMode(PENDO1, OUTPUT);
    pinMode(PENDO2, OUTPUT);
    pinMode(PENDO3, OUTPUT);
    pinMode(PENDO4, OUTPUT);
    pinMode(PENDO5, OUTPUT);
    pinMode(PENDO6, OUTPUT);
    pinMode(PENDO7, OUTPUT);
    pinMode(PENDO8, OUTPUT);
    pinMode(PENDO9, OUTPUT);
    pinMode(PENDO10, OUTPUT);
    pinMode(SERVO1, OUTPUT);
    pinMode(SERVO2, OUTPUT);
    pinMode(SERVO3, OUTPUT);
    pinMode(SERVO4, OUTPUT);
    pinMode(LED, OUTPUT);
    softPwmCreate(SERVO1, 0, 200);
    softPwmCreate(SERVO2, 0, 200);
    softPwmCreate(SERVO3, 0, 200);
    softPwmCreate(SERVO4, 0, 200);
}

int main(int argc, char *argv[], char *envp[])
{
    pid_t   child;

    if (argc != 2)
        exit(0);
    init();
    pen_move(2);
    while (1)
    {
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
