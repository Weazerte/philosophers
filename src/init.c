/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:54:43 by eaubry            #+#    #+#             */
/*   Updated: 2023/10/17 14:37:47 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->m_lst_meal[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->iter_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->end_mutex, NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].id = i;
		data->philo[i].iteration = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->number_of_philosophers;
		data->philo[i].lst_meal = 0;
		i++;
	}
	data->monitoring->data = data;
	if (i != data->number_of_philosophers)
		return (1);
	return (0);
}

int	init_malloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (1);
	data->m_lst_meal = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->m_lst_meal)
	{
		ft_free_init(data, "error lst_meal_mutex");
		return (1);
	}
	data->fork_mutex = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->fork_mutex)
	{
		ft_free_init(data, "error fork_mutex");
		return (1);
	}
	data->monitoring = malloc(sizeof(t_moni));
	if (!data->monitoring)
	{
		ft_free_init(data, "error monitoring");
		return (1);
	}
	return (0);
}

int	init_data_bis(t_data *data)
{
	if (init_malloc(data) == 1)
		return (1);
	if (init_mutex(data) == 1)
	{
		ft_free_init(data, "error data");
		return (1);
	}
	if (init_philo(data) == 1)
	{
		ft_free_init(data, "error philo");
		ft_destroy_mutex(data);
		return (1);
	}
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	(void)ac;
	(void)**av;
	data->max_iter = -1;
	data->can_i = 0;
	if (ac >= 5)
	{
		data->number_of_philosophers = ft_atoi(av[1]);
		data->ttd = ft_atoi(av[2]);
		data->tte = ft_atoi(av[3]);
		data->tts = ft_atoi(av[4]);
		data->end_sim = 0;
	}
	if (ac == 6)
	{
		data->max_iter = ft_atoi(av[5]);
		if (data->max_iter < 1)
			return (error_msg(data), 1);
	}
	if (data->number_of_philosophers < 1)
		return (error_msg(data), 1);
	if (init_data_bis(data))
		return (1);
	return (0);
}
