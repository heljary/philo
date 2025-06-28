/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:07:11 by heljary           #+#    #+#             */
/*   Updated: 2025/06/28 13:57:24 by heljary          ###   ########.fr       */
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
    while(i < rules->num_philosophers)
    {
        pthread_create(&threads[i],NULL,ft_routine,&philo[i]);
        printf("philosopher[%ld] \n",i);
        i++;
    }
    int in = 0;
    while (in < rules->num_philosophers)
    {
        pthread_join(threads[in],NULL);
        in++;
    }
    
}

// printf("| num_philosophers = %d | time_to_die = %d | time_to_eat = %d | time_to_sleep = %d | must_eat_count = %d | start_time = %ld |\n",res->num_philosophers,res->time_to_die,res->time_to_eat,res->time_to_sleep,res->must_eat_count,res->start_time);