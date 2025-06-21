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
    int time_to_eat;   
    int time_to_sleep;  
    int must_eat_count; 
    long start_time;   
    pthread_mutex_t print_mutex;
} t_rules;