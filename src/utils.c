/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:45:01 by weaz              #+#    #+#             */
/*   Updated: 2023/10/17 15:28:51 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_is_dead(t_data *data, int i)
{
	pthread_mutex_unlock(&data->m_lst_meal[i]);
	pthread_mutex_lock(&data->print);
	if (data->can_i == 1)
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	data->can_i = 1;
	printf("%ld %d died\n", (time_now() - data->start_time), i + 1);
	pthread_mutex_unlock(&data->print);
}

int	simu_delay(long int start_time)
{
	while (time_now() < start_time)
		continue ;
	return (0);
}

int	ft_destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->iter_mutex);
	pthread_mutex_destroy(&data->print);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->m_lst_meal[i]);
	free(data->m_lst_meal);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->fork_mutex[i]);
	free(data->fork_mutex);
	return (0);
}

void	ft_free_init(t_data *data, char *s)
{
	int	i;
	
	free(data->philo);
	if (s[6] == 'm')
	{
		free(data->m_lst_meal);
		free(data->fork_mutex);
	}
	else if (s[6] == 'd' || s[6] == 'p')
	{
		free(data->m_lst_meal);
		free(data->fork_mutex);
		free(data->monitoring);
	}
	i = -1;
	while(s[++i])
		write(2, &s[i], 1);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_philo(2, philo);
	ft_usleep(philo->data->tts);
	if (ft_end_sim(philo->data) == 1)
		return ;
	print_philo(3, philo);
}
