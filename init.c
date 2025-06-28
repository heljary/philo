/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:08:37 by heljary           #+#    #+#             */
/*   Updated: 2025/06/28 13:52:14 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_gettime()
{
    struct timeval tv;
    long ms;
    gettimeofday(&tv,NULL);
    ms = (tv.tv_sec * 1000) + (tv.tv_usec/100);

    return (ms);
}

void *ft_init_rules(int ac,char **args)
{
    t_rules *ini_rules = malloc(sizeof(t_rules));
    ini_rules->num_philosophers = atoi(args[1]);
    ini_rules->time_to_die = atoi(args[2]);
    ini_rules->time_to_eat = atoi(args[3]);
    ini_rules->time_to_sleep = atoi(args[4]);
    ini_rules->start_time = ft_gettime();

    if (ac == 6)
        ini_rules->must_eat_count = atoi(args[5]);
    else
        ini_rules->must_eat_count = -1;
    if (ini_rules->num_philosophers <= 0 || ini_rules->time_to_die <= 0 ||
    ini_rules->time_to_eat <= 0 || ini_rules->time_to_sleep <= 0 ||
    (ac == 6 && ini_rules->must_eat_count <= 0))
    {
        free(ini_rules);
        return NULL;
    }
    return (ini_rules);
}

void ft_init_forks(t_rules *rules)
{
    int i;
    i = 0;
    rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philosophers);
    if(!rules->forks)
        return;
    while (i < rules->num_philosophers)
    {
        pthread_mutex_init(&rules->forks[i],NULL);
        i++;
    }
}


void *ft_init_philosophers(t_rules *rules)
{
    int i;
    t_philosopher *philo;
    i = 0;
    philo = malloc(sizeof(t_philosopher) * rules->num_philosophers);
    if(!philo)
        return NULL;
    while (i < rules->num_philosophers)
    {
        philo[i].id = i + 1;
        philo[i].last_meal_time = 0;
        philo[i].times_eaten = 0;
        philo[i].left_fork = &rules->forks[i];
        philo[i].right_fork = &rules->forks[(i+1)%rules->num_philosophers];
        philo[i].rules = rules;
        i++;
    }  
    return philo;
}