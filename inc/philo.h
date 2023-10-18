/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:27:21 by eaubry            #+#    #+#             */
/*   Updated: 2023/10/17 14:13:25 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <syscall.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	*m_lst_meal;
	pthread_mutex_t	iter_mutex;
	pthread_mutex_t	print;
	long int		start_time;
	struct s_philo	*philo;
	struct s_moni	*monitoring;
	int				can_i;
	int				end_sim;
	int				number_of_philosophers;
	int				ttd;
	int				tte;
	int				tts;
	int				max_iter;

}					t_data;

typedef struct s_moni
{
	pthread_t		tid;
	t_data			*data;
}					t_moni;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	long int		lst_meal;
	t_data			*data;
	int				left_fork;
	int				right_fork;
	int				iteration;

}					t_philo;

void				ft_routine(t_data *data);

int					ft_end_sim(t_data *data);

long int			time_now(void);

int					ft_usleep(long int time);

int					ft_atoi(const char *nptr);

void				print_philo(int who, t_philo *philo);

void				philo_is_eating(t_philo *philo);

void				philo_is_sleeping(t_philo *philo);

void				*monitoring_routine(void *data_ptr);

void				*monitoring_routine_max_iter(void *data_ptr);

int					init_data(int ac, char **av, t_data *data);

int					simu_delay(long int start_time);

void				ft_free_init(t_data *data, char *s);

int					ft_destroy_mutex(t_data *data);

int					ft_isdigit(char c);

int					check_max_iter(t_data *data);

void				philo_is_dead(t_data *data, int i);

int					check_end_philo(t_philo *philo, int who);

void				start_fcked_routine(t_data *data);

void 				error_msg(t_data *data);

#endif