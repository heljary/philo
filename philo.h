#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct philosopher {
    int id; 
    int times_eaten;   
    long last_meal_time; 
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
    struct rules* rules;     
} t_philosopher;

typedef struct rules {
    int num_philosophers;   
    int time_to_die;     
    int time_to_sleep;  
    int time_to_eat;   
    int must_eat_count;
    long start_time;   
    int simulation_running;
    pthread_mutex_t print_mutex;
    pthread_mutex_t start_mutex;
    pthread_mutex_t meal_check_metuxes;
    pthread_mutex_t *forks;
} t_rules;


long ft_gettime();
void *ft_init_rules(int ac,char **args);
void ft_init_forks(t_rules *rules);
void *ft_init_philosophers(t_rules *rules);
void *ft_routine(void *args);
int	ft_usleep(size_t milliseconds);
void *ft_monitor_death(void *args);

#endif