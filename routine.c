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

void ft_print_status(char *status, t_philosopher *philo)
{
    if(!philo->rules->simulation_running)
        return;
    pthread_mutex_lock(&(philo->rules->print_mutex));
    printf("%ld %d %s\n", ft_gettime() - philo->rules->start_time, philo->id, status);
    pthread_mutex_unlock(&(philo->rules->print_mutex));
}


void philo_take_forks(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        ft_print_status("has taken a fork", philo);
        pthread_mutex_lock(philo->left_fork);
        ft_print_status("has taken a fork", philo);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print_status("has taken a fork", philo);
        pthread_mutex_lock(philo->right_fork);
        ft_print_status("has taken a fork", philo);
    }
}

void philo_eat(t_philosopher *philo)
{
    ft_print_status("is eating", philo);
    philo->last_meal_time = ft_gettime();
    ft_usleep(philo->rules->time_to_eat);
    if (philo->rules->must_eat_count != -1)
        philo->times_eaten += 1;
}

void philo_put_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void philo_sleep(t_philosopher *philo)
{
    ft_print_status("is sleeping", philo);
    ft_usleep(philo->rules->time_to_sleep);
}


void philo_think(t_philosopher *philo)
{
    ft_print_status("is thinking", philo);
    ft_usleep(1);
}


void *ft_routine(void *args)
{
    t_philosopher *philo = (t_philosopher *)args;
    if(philo->rules->num_philosophers == 1)
    {
        ft_print_status("has taken a fork", philo);
        return NULL;
    }
    if (philo->id % 2 == 0)
        ft_usleep(5);
    while (philo->rules->simulation_running)
    {
        philo_take_forks(philo);
        philo_eat(philo);
        philo_put_forks(philo);
        if (!philo->rules->simulation_running)
            break;
        philo_sleep(philo);
        philo_think(philo);
    }
    return NULL;
}
