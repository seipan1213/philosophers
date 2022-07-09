/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:36:23 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/09 22:38:19 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_err(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;

	cnt = 0;
	if (n == 0)
		return (0);
	while (s1[cnt] && s2[cnt] && cnt < n - 1)
	{
		if (s1[cnt] != s2[cnt])
			return ((unsigned char)s1[cnt] - (unsigned char)s2[cnt]);
		cnt++;
	}
	return ((unsigned char)s1[cnt] - (unsigned char)s2[cnt]);
}

int	ph_atoi(char *str)
{
	int		i;
	int		m;
	long	ans;

	i = 0;
	m = 1;
	ans = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
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
	if (i > 10 || (i == 10 && ((m == 1 && str[i - 1] - '0' > 7)
				|| (m == -1 && str[i - 1] - '0' > 8))))
		return (-1);
	return ((int)ans * m);
}

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (len--)
		*(str + len) = '\0';
}
