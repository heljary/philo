/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:08:37 by heljary           #+#    #+#             */
/*   Updated: 2025/07/19 15:03:21 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isvalidargs(t_rules *ini_rules, int ac)
{
	if (ini_rules->num_philosophers <= 0 || ini_rules->num_philosophers > 200
		|| ini_rules->time_to_die < 60 || ini_rules->time_to_eat < 60
		|| ini_rules->time_to_sleep < 60 || (ac == 6
			&& ini_rules->must_eat_count <= 0))
	{
		printf("============> please check args <============\n");
		printf("1 => number of philosophers\n");
		printf("2 => time to die\n");
		printf("3 => time to eat\n");
		printf("4 => time to sleep\n");
		printf("5 => number of times each philosopher must eat\n");
		free(ini_rules);
		return (1);
	}
	return (0);
}

void	*ft_init_rules(int ac, char **args)
{
	t_rules	*ini_rules;

	ini_rules = malloc(sizeof(t_rules));
	if (!ini_rules)
		return (NULL);
	ini_rules->num_philosophers = ft_atoi(args[1]);
	ini_rules->time_to_die = ft_atoi(args[2]);
	ini_rules->time_to_eat = ft_atoi(args[3]);
	ini_rules->time_to_sleep = ft_atoi(args[4]);
	ini_rules->start_time = ft_gettime();
	ini_rules->simulation_running = 1;
	if (ac == 6)
		ini_rules->must_eat_count = ft_atoi(args[5]);
	else
		ini_rules->must_eat_count = -1;
	if (ft_isvalidargs(ini_rules, ac))
		return (NULL);
	pthread_mutex_init(&(ini_rules->print_mutex), NULL);
	pthread_mutex_init(&(ini_rules->meal_check_metuxes), NULL);
	pthread_mutex_init(&(ini_rules->end_mutex), NULL);
	return (ini_rules);
}

void	ft_init_forks(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philosophers);
	if (!rules->forks)
		return ;
	while (i < rules->num_philosophers)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}

void	*ft_init_philosophers(t_rules *rules)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = malloc(sizeof(t_philosopher) * rules->num_philosophers);
	if (!philo)
		return (NULL);
	while (i < rules->num_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].last_meal_time = rules->start_time;
		philo[i].times_eaten = 0;
		philo[i].left_fork = &rules->forks[i];
		philo[i].right_fork = &rules->forks[(i + 1) % rules->num_philosophers];
		philo[i].rules = rules;
		i++;
	}
	return (philo);
}
