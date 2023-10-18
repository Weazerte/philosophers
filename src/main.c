/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:36:24 by eaubry            #+#    #+#             */
/*   Updated: 2023/10/17 14:34:03 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_pars(char **av, int ac)
{
	int		i;
	int		count;
	size_t	j;

	i = 1;
	count = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			count += ft_isdigit(av[i][j]);
			j++;
		}
		i++;
	}
	return (count);
}

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	n_time;

	n_time = time_now() + time;
	while (time_now() < n_time)
	{
		usleep(100);
	}
	return (1);
}

void	ft_free(t_data *data)
{
	free(data->philo);
	free(data->monitoring);
	ft_destroy_mutex(data);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	data;

	if (ac >= 5 && ac <= 6)
	{
		if (ft_pars(av, ac) != 0)
			return (0);
		if (init_data(ac, av, &data) == 1)
			return (0);
		ft_routine(&data);
		pthread_join(data.monitoring->tid, NULL);
		i = -1;
		while (++i < data.number_of_philosophers)
			pthread_join(data.philo[i].tid, NULL);
		ft_free(&data);
	}
	return (0);
}
