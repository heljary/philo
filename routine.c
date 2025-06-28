/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:17 by heljary           #+#    #+#             */
/*   Updated: 2025/06/28 14:37:41 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_routine(void *args)
{
    t_philosopher *philo = (t_philosopher *)args;
    while(1){
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        } else {
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        printf("has taken a fork\n");
        philo->last_meal_time = ft_gettime();
        philo->times_eaten += 1;
        printf("Eat (update time)\n");
        usleep(1000);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        printf("Sleep (wait time)\n");
        usleep(1000);
        printf("Think (optional wait)\n");
        usleep(1000);
        if(ft_gettime() - philo->last_meal_time < philo->rules->time_to_die)
            break;
    }

    return philo;
}