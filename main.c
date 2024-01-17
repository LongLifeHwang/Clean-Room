//Programing
//python, c

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
        printf("code start");
}

int main(int argc, char *argv[], char *envp[])
{
    pid_t   child;

    if (argc != 2)
        exit (0);
    while (1)
    {
        child = fork();  //python3 yolo
        if (child < 0)
            exit (1);
        else if (child == 0) // child
            child_process(argv, envp);
        else  //parents
            parents_process();
    }
    exit (0);
}
