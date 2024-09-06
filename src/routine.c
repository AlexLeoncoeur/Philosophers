/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:21:31 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/06 15:51:28 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_sleep(int time)
{
	int	x;

	x = ft_get_time();
	while (1)
	{
		if (ft_get_time() - x >= time)
			break ;
		usleep(10);
	}
}

void	ft_message(t_philo *philo, int x)
{
	if (philo->data->death == 1)
		return ;
	pthread_mutex_lock(philo->messenger);
	if (x == 0)
		printf("%s %d Philosopher took a fork!\n%s", G, philo->id, RST);
	else if (x == 1)
		printf("%s %d Philosopher is eating!\n%s", B, philo->id, RST);
	else if (x == 2)
		printf("%s %d Philosopher is sleeping!\n%s", Y, philo->id, RST);
	else if (x == 3)
		printf("%s %d Philosopher is thinking!\n%s", M, philo->id, RST);
	else if (x == 4)
		printf("%s %d Philosopher is dead!\n%s", RED, philo->id, RST);
	pthread_mutex_unlock(philo->messenger);
}

int	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 1)
		printf("%sError: gettimeofday() failed\n%s", RED, RST);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*philo_routine(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	if (philo->id % 2 == 0)
		usleep(10);
	while (philo->data->death == 0)
	{
		pthread_mutex_lock(&philo->fork_l);
		ft_message(philo, 0);
		pthread_mutex_lock(&philo->fork_r);
		ft_message(philo, 0);
		philo->time_death = philo->data->time_die;
		ft_message(philo, 1);
		philo->times_eaten++;
		philo->last_eat = ft_get_time() - philo->data->start;
		ft_sleep(philo->data->time_eat);
		pthread_mutex_unlock(&philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
		ft_message(philo, 2);
		ft_sleep(philo->data->time_sleep);
		ft_message(philo, 3);
	}
	return (NULL);
}

void	ft_create_philo(t_data *data)
{
	data->start = ft_get_time();
	data->i = 0;
	pthread_create(&data->monitor, NULL, &ft_monitoring, (void *)data);
	while (data->i < data->philo_nb)
	{
		if (pthread_create(&data->philosophers[data->i].thread, NULL, &philo_routine, (void *)&data->philosophers[data->i]) != 0)
			ft_puterrorstr("Error: Failed to create philosopher\n", data);
		data->i++;
	}
	data->i = 0;
	pthread_join(data->monitor, NULL);
	while (data->i < data->philo_nb)
	{
		if (pthread_join(data->philosophers[data->i].thread, NULL) != 0)
			ft_puterrorstr("Error: Failed to join philosopher\n", data);
		data->i++;
	}
}
