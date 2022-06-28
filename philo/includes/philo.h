#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define ARG_ERR "ARGERR"
#define MALLOC_ERR "MALLOCERR"
#define MUTEX_ERR "MUTEXERR"

typedef struct s_men
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_mutex_t *died;
	pthread_mutex_t *eat;
	int *eat_cnt;
	int id;
} t_men;

typedef struct s_philo
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *forks;
	t_men *men;
	pthread_mutex_t died;
	pthread_mutex_t eat;
	int eat_cnt;
} t_philo;

int ph_free(t_philo *ph, int ret);

int put_err(char *str);
size_t ft_strlen(char *str);
int ft_atoi(char *str);
void ft_bzero(void *s, size_t len);

#endif
