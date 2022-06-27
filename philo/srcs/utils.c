#include "philo.h"

void put_endl_fd(char *str, int fd)
{
	size_t len;

	len = ft_strlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
}

size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}