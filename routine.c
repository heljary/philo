/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:17 by heljary           #+#    #+#             */
/*   Updated: 2025/07/19 17:06:03 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philosopher *philo)
{
	ft_print_status("is eating", philo);
	pthread_mutex_lock(&philo->rules->meal_check_metuxes);
	philo->last_meal_time = ft_gettime();
	pthread_mutex_unlock(&philo->rules->meal_check_metuxes);
	pthread_mutex_lock(&philo->rules->end_mutex);
	if (philo->rules->must_eat_count != -1)
		philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->rules->end_mutex);
	ft_usleep(philo->rules, philo->rules->time_to_eat);
}

void	philo_put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philosopher *philo)
{
	ft_print_status("is sleeping", philo);
	ft_usleep(philo->rules, philo->rules->time_to_sleep);
}

void	philo_think(t_philosopher *philo)
{
	ft_print_status("is thinking", philo);
}

void	*ft_routine(void *args)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)args;
	while (1)
	{
		if (philo->rules->must_eat_count != -1 && philo->times_eaten >= philo->rules->must_eat_count)	
			break;
		pthread_mutex_lock(&philo->rules->end_mutex);
		if (!philo->rules->simulation_running)
		{
			pthread_mutex_unlock(&philo->rules->end_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->rules->end_mutex);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_put_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
		usleep(1000);
	}
	return (NULL);
}
