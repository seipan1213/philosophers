#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define ARG_ERR "Error\nargsNum: 4 or 5(range: int)\nphiloNum max:200   other min:60"
#define MALLOC_ERR "Error\nmalloc"
#define MUTEX_ERR "Error\nmutex"

#define PIC_FORK "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIED "died"

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
	pthread_mutex_t eat;
	pthread_mutex_t *print;
	int eat_cnt;
	int id;
	long last_eat_time;
	pthread_t thread;
	bool *is_fin;
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
	pthread_mutex_t print;
	bool is_fin;
} t_philo;

void ph_work_think(t_man *man);
void ph_work_eat(t_man *man);
void ph_work_sleep(t_man *man);
void *ph_work(void *arg);
void ph_main(t_philo *ph);

int put_err(char *str);
size_t ft_strlen(char *str);
int ph_atoi(char *str);
void ft_bzero(void *s, size_t len);
long get_time_ms(void);

void man_sleep(long sleep_time, t_man *man);

int get_eat_cnt(t_man *man);
bool get_is_fin(t_man *man);
void set_is_fin(t_man *man, bool is_fin);
long get_last_eat_time(t_man *man);
void set_last_eat_time(t_man *man);

bool ph_args_init(int argc, char **argv, t_philo *ph);
bool ph_men_init(t_philo *ph);
bool ph_main_init(t_philo *ph);
bool ph_init(int argc, char **argv, t_philo *ph);

int ph_free(t_philo *ph, int ret);
void ph_end(t_philo *ph);
void ph_put_log(t_man *man, char *str);

void ph_watcher(void *arg);
#endif
