#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define ARG_ERR "ARGERR"

int put_err(char *str);
size_t ft_strlen(char *str);
int ft_atoi(char *str);
void ft_bzero(void *s, size_t len);

#endif
