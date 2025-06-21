#include "philo.h"

void *function(void *arg)
{
    pthread_mutex_t *fork = (pthread_mutex_t *)arg;
    pthread_mutex_lock(fork);
    printf("Thread locked mutex\n");
    pthread_mutex_unlock(fork);
    return NULL;
}

int main()
{
    int number_philo = 5;
    pthread_mutex_t forks[number_philo];
    pthread_t philo_threads[number_philo];
    int i = 0;
    while(i<number_philo)
    {
        pthread_mutex_init(&forks[i],NULL);
        i++;
    }
    int ii=0;
    while(ii<number_philo){
        pthread_create(&philo_threads[ii],NULL,&function,&forks[ii]);
        ii++;
    }

    int iii = 0;
    while(iii<number_philo)
    {
        pthread_join(philo_threads[iii],NULL);
        iii++;
    }

    int iiii=0;
    while(iiii<number_philo)
    {
        pthread_mutex_destroy(&forks[iii]);
        iiii++;
    }
}