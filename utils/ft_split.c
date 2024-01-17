#include "../clean_room.h"

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