/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:42:22 by weaz              #+#    #+#             */
/*   Updated: 2023/10/17 18:07:41 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring_routine(void *data_ptr)
{
	int			i;
	long int	now;
	t_data		*data;

	data = (t_data *)data_ptr;
	simu_delay(data->start_time);
	while (ft_end_sim(data) == 0)
	{
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->m_lst_meal[data->philo[i].id]);
			now = time_now() - data->philo[i].lst_meal;
			if (now >= data->ttd)
			{
				printf("%d - %ld - %ld - %d\n", i, data->philo[i].lst_meal - data->start_time, time_now() - data->start_time, data->philo[i].iteration);
				pthread_mutex_lock(&data->end_mutex);
				data->end_sim = 1;
				pthread_mutex_unlock(&data->end_mutex);
				philo_is_dead(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->m_lst_meal[data->philo[i].id]);
		}
	}
	return (NULL);
}

void	*monitoring_routine_max_iter(void *data_ptr)
{
	int			i;
	long int	now;
	t_data		*data;

	data = (t_data *)data_ptr;
	simu_delay(data->start_time);
	while (ft_end_sim(data) == 0)
	{
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->m_lst_meal[data->philo[i].id]);
			now = time_now() - data->philo[i].lst_meal;
			if (now >= data->ttd || check_max_iter(data) == 0)
			{
				pthread_mutex_lock(&data->end_mutex);
				data->end_sim = 1;
				pthread_mutex_unlock(&data->end_mutex);
				if (check_max_iter(data) == 1)
				{
					printf("%d - %ld - %ld - %d\n", i, data->philo[i].lst_meal - data->start_time, time_now() - data->start_time, data->philo[i].iteration);
					philo_is_dead(data, i);
					continue ;
				}	
			}
			pthread_mutex_unlock(&data->m_lst_meal[data->philo[i].id]);
		}
	}
	return (NULL);
}
