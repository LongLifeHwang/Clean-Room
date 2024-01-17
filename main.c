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
static void    child_process(int fd[2], char *argv[], char *envp[])
{
    char    **command;

    command = ft_split(argv[1]);
    if (command == NULL)
        exit (1);
    execve("/usr/bin/python3", command, envp);
}

static void     parents_process(int fd[2], char *argv[])
{
    int     status;

    wait(&status);
    if (status == 0)
        //code;
    exit (1);
}

int main(int argc, char *argv[], char *envp[])
{
    pid_t   child;
    int     fd[2];

    if (argc != 2)
        exit (0);
    child = fork();  //python3 yolo
    if (child < 0)
        exit (1);
    else if (child == 0) // child
        child_process(fd, argv, envp);
    else  //parents
        parents_process(fd, argv, envp);
    exit (0);
}
