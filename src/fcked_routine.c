/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcked_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:39:09 by weaz              #+#    #+#             */
/*   Updated: 2023/10/17 16:43:17 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat_timed(t_philo *philo, int t2e)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->data->fork_mutex[philo->left_fork]);
	else
		pthread_mutex_lock(&philo->data->fork_mutex[philo->right_fork]);
	print_philo(0, philo);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->data->fork_mutex[philo->right_fork]);
	else
		pthread_mutex_lock(&philo->data->fork_mutex[philo->left_fork]);
	print_philo(0, philo);
	pthread_mutex_lock(&philo->data->m_lst_meal[philo->id]);
	philo->lst_meal = time_now();
	pthread_mutex_unlock(&philo->data->m_lst_meal[philo->id]);
	print_philo(1, philo);
	ft_usleep(t2e);
	pthread_mutex_lock(&philo->data->iter_mutex);
	++philo->iteration;
	pthread_mutex_unlock(&philo->data->iter_mutex);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->right_fork]);
}

void	philo_sleep_timed(t_philo *philo, int t2s)
{
	print_philo(2, philo);
	ft_usleep(t2s);
	print_philo(3, philo);
}

void	routine_timed(t_philo *philo)
{
	int	t2e;
	int	t2s;

	t2e = philo->data->tte;
	t2s = philo->data->tts;
	if (philo->data->tte > philo->data->tts)
		t2e = (philo->data->ttd - philo->data->tts);
	else
		t2s = (philo->data->ttd - philo->data->tte);
	philo_eat_timed(philo, t2e);
	philo_sleep_timed(philo, t2s);
}

void	*fcked_routine(void *data_ptr)
{
	t_philo	*philo;
	int		wait;

	philo = (t_philo *)data_ptr;
	simu_delay(philo->data->start_time);
	if (philo->data->tte > philo->data->tts)
		wait = (philo->data->ttd - philo->data->tts);
	else
		wait = (philo->data->ttd - philo->data->tte);
	if (philo->id % 2 == 0)
		ft_usleep(wait * 0.9 + 1);
	if ((philo->data->number_of_philosophers % 2 == 1)
		&& (philo->id == (philo->data->number_of_philosophers - 1)))
		ft_usleep(wait);
	if (philo->data->number_of_philosophers == 1)
		return (print_philo(0, philo), NULL);
	while (ft_end_sim(philo->data) == 0)
		routine_timed(philo);
	return (NULL);
}

void	start_fcked_routine(t_data *data)
{
	int	i;

	data->start_time = time_now() + (data->number_of_philosophers * 20);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_create(&data->philo[i].tid, NULL, &fcked_routine,
			&data->philo[i]);
	if (data->max_iter == -1)
		pthread_create(&data->monitoring->tid, NULL, &monitoring_routine, data);
	else
		pthread_create(&data->monitoring->tid, NULL,
			&monitoring_routine_max_iter, data);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->m_lst_meal[data->philo[i].id]);
		data->philo[i].lst_meal = data->start_time;
		pthread_mutex_unlock(&data->m_lst_meal[data->philo[i].id]);
	}
}
