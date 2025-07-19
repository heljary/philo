/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_function.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:54 by heljary           #+#    #+#             */
/*   Updated: 2025/07/19 14:35:49 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(char *status, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->rules->end_mutex);
	if (!philo->rules->simulation_running)
	{
		pthread_mutex_unlock(&philo->rules->end_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->end_mutex);
	pthread_mutex_lock(&(philo->rules->print_mutex));
	printf("%ld %d %s\n", ft_gettime() - philo->rules->start_time, philo->id,
		status);
	pthread_mutex_unlock(&(philo->rules->print_mutex));
}

void	philo_take_forks(t_philosopher *philo)
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
