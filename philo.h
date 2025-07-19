/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:35:11 by heljary           #+#    #+#             */
/*   Updated: 2025/07/19 16:13:03 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philosopher
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct rules	*rules;
}					t_philosopher;

typedef struct rules
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				must_eat_count;
	long			start_time;
	int				simulation_running;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	meal_check_metuxes;
	pthread_mutex_t	*forks;
}					t_rules;

typedef struct s_value
{
	int i;
	int count;
}	t_value;

long				ft_gettime(void);
void				*ft_init_rules(int ac, char **args);
void				ft_init_forks(t_rules *rules);
void				*ft_init_philosophers(t_rules *rules);
void				*ft_routine(void *args);
// int					ft_usleep(size_t milliseconds);
int	ft_usleep(t_rules *rules,size_t milliseconds);
void				*ft_monitor_death(void *args);
int					ft_isdigit(int c);
int					check_args(char *str);
long				ft_atoi(char *str);
void	philo_take_forks(t_philosopher *philo);
void				ft_print_status(char *status, t_philosopher *philo);

#endif