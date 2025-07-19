/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:11 by heljary           #+#    #+#             */
/*   Updated: 2025/07/15 12:38:15 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_philosopher *philo, long i, pthread_t *threads)
{
	while (i < philo->rules->num_philosophers)
	{
		pthread_create(&threads[i], NULL, ft_routine, &philo[i]);
		i++;
	}
}

void	join_pthreads(t_rules *rules, long i, pthread_t *threads)
{
	while (i < rules->num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	ch_args(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!check_args(args[i]))
		{
			printf("arg [%s] is not valid \n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **args)
{
	long			i;
	t_rules			*rules;
	t_philosopher	*philo;
	pthread_t		monitor;
	pthread_t		*threads;

	if (ac != 5 && ac != 6)
		return (1);
	if (ch_args(args) == 1)
		return (1);
	i = 0;
	rules = ft_init_rules(ac, args);
	if (!rules)
		return (0);
	threads = malloc(sizeof(pthread_t) * rules->num_philosophers);
	ft_init_forks(rules);
	philo = ft_init_philosophers(rules);
	create_thread(philo, i, threads);
	pthread_create(&monitor, NULL, ft_monitor_death, &philo);
	i = 0;
	join_pthreads(rules, i, threads);
	pthread_join(monitor, NULL);
}
