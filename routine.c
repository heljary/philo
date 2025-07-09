/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:17 by heljary           #+#    #+#             */
/*   Updated: 2025/07/09 13:59:52 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"








void philo_eat(t_philosopher *philo){
    while()
}

void ft_print_status(char *status, t_philosopher *philo)
{
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (philo->rules->simulation_running) {
        printf("%ld %d %s\n", 
              ft_gettime() - philo->rules->start_time,
              philo->id, 
              status);
    }
    pthread_mutex_unlock(&philo->rules->print_mutex);
}

void ft_eat_routine(t_rules *rules, t_philosopher *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        ft_print_status("has taken a fork", philo);
        pthread_mutex_lock(philo->left_fork);
        ft_print_status("has taken a fork", philo);
        ft_print_status("is eating", philo);
        ft_usleep((size_t)(rules->time_to_eat));
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print_status("has taken a fork", philo);
        pthread_mutex_lock(philo->right_fork);
        ft_print_status("has taken a fork", philo);
        ft_print_status("is eating", philo);
        ft_usleep((size_t)(rules->time_to_eat));
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
    if (rules->must_eat_count != -1)
        philo->times_eaten += 1;
}

void *ft_routine(void *args)
{
    t_philosopher *philo = (t_philosopher *)args;
    t_rules *rules = philo->rules;
    if(philo->id % 2 == 0)
            ft_usleep(100);
    while(rules->simulation_running)
    {
        ft_eat_routine(rules, philo);
        if (!rules->simulation_running)
            break;
        ft_print_status("is sleeping", philo);
        ft_usleep((size_t)(rules->time_to_sleep));
        ft_print_status("is thinking", philo);
        ft_usleep(10);
    }
    return NULL;
}
