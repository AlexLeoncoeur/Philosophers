/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:21:31 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/11 13:00:12 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_sleep(int time)
{
	int	initial_time;

	initial_time = ft_get_time();
	while (ft_get_time() - initial_time < time)
		usleep(10);
}

void	ft_message(t_philo *philo, int x)
{
	int	i;

	pthread_mutex_lock(philo->killer);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(philo->killer);
		return ;
	}
	pthread_mutex_unlock(philo->killer);
	pthread_mutex_lock(philo->messenger);
	i = ft_get_time() - philo->data->start;
	pthread_mutex_lock(philo->killer);
	if (x == 0 && philo->data->death != 1)
		printf("%s%d %d has taken a fork\n%s", G, i, philo->id, RST);
	else if (x == 1 && philo->data->death != 1)
		printf("%s%d %d is eating\n%s", B, i, philo->id, RST);
	else if (x == 2 && philo->data->death != 1)
		printf("%s%d %d is sleeping\n%s", Y, i, philo->id, RST);
	else if (x == 3 && philo->data->death != 1)
		printf("%s%d %d is thinking\n%s", M, i, philo->id, RST);
	else if (x == 4 && philo->data->death != 1)
		printf("%s%d %d died\n%s", RED, i, philo->id, RST);
	pthread_mutex_unlock(philo->killer);
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
	if (!(philo->id % 2))
		ft_sleep(100);
	while (1)
	{
		if (philo->data->philo_nb == 1)
		{
			ft_lonely_philo(philo);
			break ;
		}
		ft_eat(philo);
		pthread_mutex_lock(&philo->data->killer);
		if (philo->data->death == 1)
		{
			pthread_mutex_unlock(&philo->data->killer);
			break ;
		}
		pthread_mutex_unlock(&philo->data->killer);
		ft_sleep_action(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_get_time();
	pthread_create(&data->monitor, NULL, &ft_monitoring, (void *)data);
	while (i < data->philo_nb)
	{
		pthread_create(&data->philosophers[i].thread, NULL,
			&philo_routine, (void *)&data->philosophers[i]);
		i++;
	}
	i = 0;
	pthread_join(data->monitor, NULL);
	while (i < data->philo_nb)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}
