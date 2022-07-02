#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define ARG_ERR "ARGERR"
#define MALLOC_ERR "MALLOCERR"
#define MUTEX_ERR "MUTEXERR"

#define PIC_FORK "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIED "died"

#define TIME_INTERVAL 500 // NOTE: 数msズレる問題

typedef struct s_man
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_mutex_t *fin;
	pthread_mutex_t *eat;
	pthread_mutex_t last_eat;
	int *eat_cnt;
	int id;
	long last_eat_time;
	pthread_t thread;
	bool *is_fin;
	pthread_t watcher;
} t_man;

typedef struct s_philo
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *forks;
	t_man *men;
	pthread_mutex_t fin;
	pthread_mutex_t eat;
	int eat_cnt;
	bool is_fin;
} t_philo;

int ph_free(t_philo *ph, int ret);

int put_err(char *str);
size_t ft_strlen(char *str);
int ft_atoi(char *str);
void ft_bzero(void *s, size_t len);
long get_time_ms(void);
void ms_sleep(long ms);

#endif
