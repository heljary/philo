/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:08:37 by heljary           #+#    #+#             */
/*   Updated: 2025/06/28 06:17:54 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_gettime()
{
    struct timeval tv;
    long ms;
    gettimeofday(&tv,NULL);
    //1000ms = 1s and 1ms = 1000mic
    ms = (tv.tv_sec * 1000) + (tv.tv_usec/100);

    return (ms);
}

void ft_forks(t_rules *rules)
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


void *init_philosophers(t_philosopher *philo)
{
    int i;
    i = 0;
    philo = malloc(sizeof(t_philosopher) * philo->rules->num_philosophers);
    if(!philo)
        return;
    while ()
    {
        /* code */
    }
    
    
}