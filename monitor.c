/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 05:21:36 by heljary           #+#    #+#             */
/*   Updated: 2025/07/19 15:50:18 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_died(t_philosopher **philosopher, t_value *var)
{
	while (var->i < (*philosopher)->rules->num_philosophers)
	{
		pthread_mutex_lock(&(*philosopher)->rules->meal_check_metuxes);
		if ((ft_gettime()
				- (*philosopher)[var->i].last_meal_time)
				> (*philosopher)->rules->time_to_die)
		{
			ft_print_status("died", &(*philosopher)[var->i]);
			pthread_mutex_lock(&(*philosopher)->rules->end_mutex);
			(*philosopher)->rules->simulation_running = 0;
			pthread_mutex_unlock(&(*philosopher)->rules->end_mutex);
		}
		pthread_mutex_unlock(&(*philosopher)->rules->meal_check_metuxes);
		pthread_mutex_lock(&(*philosopher)->rules->end_mutex);
		if (((*philosopher)[var->i].times_eaten
			>= (*philosopher)->rules->must_eat_count)
			&& (*philosopher)->rules->must_eat_count != -1)
		{
			var->count++;
		}
		pthread_mutex_unlock(&(*philosopher)->rules->end_mutex);
		var->i++;
	}
	return ;
}

void	*ft_monitor_death(void *args)
{
	t_philosopher	**philosopher;
	t_value			*var;
	int				n;

	var = malloc(sizeof(t_value));
	philosopher = (t_philosopher **)args;
	pthread_mutex_lock(&(*philosopher)->rules->end_mutex);
	n = (*philosopher)->rules->simulation_running;
	pthread_mutex_unlock(&(*philosopher)->rules->end_mutex);
	while (n)
	{
		var->count = 0;
		var->i = 0;
		check_died(philosopher, var);
		pthread_mutex_lock(&(*philosopher)->rules->end_mutex);
		if (var->count == (*philosopher)->rules->num_philosophers)
		{
			(*philosopher)->rules->simulation_running = 0;
			pthread_mutex_unlock(&(*philosopher)->rules->end_mutex);
			return NULL;
		}
		pthread_mutex_unlock(&(*philosopher)->rules->end_mutex);
		pthread_mutex_lock(&(*philosopher)->rules->end_mutex);
		n = (*philosopher)->rules->simulation_running;
		pthread_mutex_unlock(&(*philosopher)->rules->end_mutex);
		usleep(1000);
	}
	return (NULL);
}
