/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:11 by heljary           #+#    #+#             */
/*   Updated: 2025/07/09 13:28:58 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac,char **args)
{
    long i = 0;
    if(ac != 5 && ac != 6)
    {
        return 1;
    }
    t_rules *rules = ft_init_rules(ac,args);
    ft_init_forks(rules);
    t_philosopher *philo = ft_init_philosophers(rules);
    pthread_t threads[rules->num_philosophers];
    pthread_t monitor;
    while(i < rules->num_philosophers)
    {
        pthread_create(&threads[i],NULL,ft_routine,&philo[i]);
        i++;
    }
    pthread_create(&monitor,NULL,ft_monitor_death, &philo);
    i = 0;
    while(i < rules->num_philosophers)
    {
        pthread_join(threads[i],NULL);
        i++;
    }
    pthread_join(monitor,NULL);
}
