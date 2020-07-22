#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	len = 0;

	while (*str++)
		len++;
	return (len);
}

static int	ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	if (*str == '\0' && c == '\0')
		return (1);
	return (0);
}

static char	*ft_strdup(char *str)
{
	char	*ret;
	int		i = -1;

	if (!(ret = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[++i])
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

static char	*ft_strjoin(char *str1, char *str2)
{
	char	*ret;
	int		i = -1;
	int		j = -1;
	int		len = ft_strlen(str1) + ft_strlen(str2);

	if (!str1 || !str2)
		return (ft_strdup(""));
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str1[++i])
		ret[i] = str1[i];
	while (str2[++j])
		ret[i + j] = str2[j];
	ret[i + j] = '\0';
	return (ret);
}

static char	*ft_substr(char *str, int start, int len)
{
	char	*ret;
	int		i = start;
	int		j = -1;

	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (++j < len && str)
		ret[j] = str[i++];
	ret[j] = '\0';
	return (ret);
}

static char	*ft_clean_list(char **line, char *list, int size)
{
	char	*tmp;
	int		len = ft_strlen(list);
	int		i = -1;

	while (list[++i])
		if (list[i] == '\n')
			break ;
	if (i < len)
	{
		*line = ft_substr(list, 0, i);
		tmp = ft_substr(list, i + 1, len);
		free(list);
		list = tmp;
	}
	else if (size == 0)
	{
		*line = list;
		list = NULL;
	}
	return (list);
}

static char	*ft_list(char *list, char *buf)
{
	char	*tmp;

	if (list)
	{
		tmp = ft_strjoin(list, buf);
		free(list);
		list = tmp;
	}
	else
		list = ft_strdup(buf);
	return (list);
}

int			get_next_line(char **line)
{
	static char	*list;
	char		buf[BUFFER_SIZE + 1];
	int			size = 0;
	int			fd = 0;

	if (line == NULL || read(fd, buf, 0) != 0)
		return (-1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (size < 0)
			return (-1);
		buf[size] = '\0';
		if (!(list = ft_list(list, buf)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (size <= 0 && !list)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!(list = ft_clean_list(line, list, size)))
		return (0);
	return (1);
}

#include <stdio.h>

int		main(void)
{
	char	*line;

	while (get_next_line(&line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
}
