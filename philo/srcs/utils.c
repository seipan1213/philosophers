#include "philo.h"

int put_err(char *str)
{
	size_t len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int ft_atoi(char *str) // TODO:修正予定
{
	int i;
	int m;
	long ans;

	i = 0;
	m = 1;
	ans = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' ||
		   str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		m = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans *= 10;
		ans += str[i++] - '0';
	}
	return ((int)ans * m);
}

void ft_bzero(void *s, size_t len)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (len--)
		*(str + len) = '\0';
}

long get_time_ms(void)
{
	struct timeval time;
	long msec;

	gettimeofday(&time, NULL);
	msec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (msec);
}