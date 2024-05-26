
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"
# include "stddef.h"
# include "lem_in.h"

char	*ft_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}



char	*ft_strdup(char *str)
{
	char	*res;
	int	i;

	i = 0;
	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	res[ft_strlen(str)] = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

char	*ft_strjoin(char *first, char *second)
{
	char	*res;
	int	first_len;
	int	second_len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!first || !second)
		return (NULL);
	first_len = ft_strlen(first);
	second_len = ft_strlen(second);
	res = malloc(sizeof(char) * first_len + second_len + 1);
	res[first_len + second_len] = 0;
	while (first[j])
	{
		res[i] = first[j];
		i++;
		j++;
	}
	j = 0;
	while (second[j])
	{
		res[i] = second[j];
		j++;
		i++;
	}
	free(first);
	return (res);
}

void	ft_bzero(char *str, int len)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i != len)
	{
		str[i] = 0;
		i++;
	}
}

char	*ft_retclean(char *line, char *keep)
{
	int	i;
	int	j;
	char	*res;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	res = malloc(sizeof(char) * i + 1);
	res[i] = 0;
	while (j < i)
	{
		res[j] = line[j];
		j++;
	}
	j = 0;
	ft_bzero(keep, BUFFER_SIZE);
	while (line[i])
	{
		keep[j] = line[i];
		i++;
		j++;
	}
	free(line);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	keep[BUFFER_SIZE + 1] = {0};
	char		*line;

	line = NULL;
	if (keep[0] != 0)
	{
		line = ft_strdup(keep);
		if (ft_strchr(line, '\n') != NULL)
			return (ft_retclean(line, keep));
		ft_bzero(keep, BUFFER_SIZE);
	}
	while (read(fd, keep, BUFFER_SIZE) > 0)
	{
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin(line, keep);
		if (ft_strchr(line, '\n') != NULL)
			return (ft_retclean(line, keep));
		ft_bzero(keep, BUFFER_SIZE);
	}
	return (line);
}
