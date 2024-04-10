# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>

static size_t	row_size(char *str, char c)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c)
			size++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (size);
}

static char	*make_arr(char *str, char c)
{
	size_t	len;
	char	*arr_small;
	size_t	i;

	len = 0;
	while (*(str + len) && *(str + len) != c)
		len++;
	arr_small = (char *)malloc(sizeof(char) * (len + 1));
	if (arr_small == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		arr_small[i] = *(str + i);
		i++;
	}
	arr_small[i] = '\0';
	return (arr_small);
}

static int	ft_free(char **arr, size_t index)
{
	if (arr[index] != NULL)
		return (0);
	while (index > 0)
	{
		free(arr[index]);
		index--;
	}
	free(arr[index]);
	free(arr);
	return (1);
}

static char	**str_split(char *str, char c, size_t size)
{
	char	**arr;
	size_t	i;
	size_t	index;

	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == NULL)
		return (0);
	index = 0;
	i = 0;
	while (*(str + i))
	{
		while (*(str + i) && *(str + i) == c)
			i++;
		if (*(str + i) != c && *(str + i))
		{
			arr[index] = make_arr((str + i), c);
			if (ft_free(arr, index))
				return (0);
			index++;
		}
		while (*(str + i) && *(str + i) != c)
			i++;
	}
	arr[index] = 0;
	return (arr);
}

char	**ft_split(char *str, char c)
{
	size_t	size;

	size = row_size(str, c);
	return (str_split(str, c, size));
}

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
    int i = 0;

	while (1)
	{
		waitpid(-1, &status, WNOHANG);
		printf("WIFEXITED(status) : %d\n", WIFEXITED(status));
		if (WIFEXITED(status))
		{
			break ;
		}
		if (i == 31) //answer : 1
		{
			kill(-1, SIGKILL);
			break ;
		}
        i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
    pid_t   child;

    child = fork();
    if (child < 0)
        return (0);
    else if (child == 0)
        child_process(argv, envp);
    else
        parents_process();
    return (0);
}

