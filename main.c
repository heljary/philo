/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:11 by heljary           #+#    #+#             */
/*   Updated: 2025/06/28 05:07:12 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void forks()
{
    t_rules *rules;
    rules->forks = malloc(sizeof(rules) * 5);
}


int main(int ac,char **argv)
{
    t_rules *philo = malloc(sizeof(t_rules));
    if(ac != 5 && ac != 6)
    {
       return 1;
    }

    philo->num_philosophers = atoi(argv[1]);
    philo->time_to_die = atoi(argv[2]);
    philo->time_to_eat = atoi(argv[3]);
    philo->time_to_sleep = atoi(argv[4]);
    philo->start_time = get_time();

    if (ac == 6)
        philo->must_eat_count = atoi(argv[5]);
    else
        philo->must_eat_count = -1;
    if (philo->num_philosophers <= 0 || philo->time_to_die <= 0 ||
    philo->time_to_eat <= 0 || philo->time_to_sleep <= 0 ||
    (ac == 6 && philo->must_eat_count <= 0))
        return 1;
    printf("%d\n",philo->num_philosophers);
    printf("%d\n",philo->time_to_die);
    printf("%d\n",philo->time_to_eat);
    printf("%d\n",philo->time_to_sleep);
    printf("%d\n",philo->must_eat_count);
    printf("%ld\n",philo->start_time);
}
