/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 05:21:36 by heljary           #+#    #+#             */
/*   Updated: 2025/07/09 13:56:12 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_monitor_death(void *args)
{
    t_philosopher **philosopher = (t_philosopher **)args;
    int i;
    int count;
    while((*philosopher)->rules->simulation_running)
    {
        i = 0;
        count = 0;
        while(i < (*philosopher)->rules->num_philosophers)
        {
            pthread_mutex_lock(&(*philosopher)->rules->meal_check_metuxes);
            if((ft_gettime() - (*philosopher)[i].last_meal_time) > (*philosopher)->rules->time_to_die)
            {
                pthread_mutex_lock(&(*philosopher)->rules->print_mutex);
                printf("%ld %d died\n",ft_gettime() - (*philosopher)[i].rules->start_time,(*philosopher)[i].id);
                pthread_mutex_unlock(&(*philosopher)->rules->print_mutex);
                (*philosopher)->rules->simulation_running = 0;
                pthread_mutex_unlock(&(*philosopher)->rules->meal_check_metuxes);
                break;;
            }
            if(((*philosopher)[i].times_eaten >= (*philosopher)->rules->must_eat_count) && (*philosopher)->rules->must_eat_count != -1)
                count++;
            pthread_mutex_unlock(&(*philosopher)->rules->meal_check_metuxes);
            i++;
        }
        if (count == i)
            (*philosopher)->rules->simulation_running = 0;
        ft_usleep(5);
    }
    return NULL;
}