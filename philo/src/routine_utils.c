/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:58:06 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/12 11:30:45 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	ft_message(philo, 0);
	pthread_mutex_unlock(philo->fork_l);
	ft_sleep(philo->data->time_die);
}

int	ft_get_death(t_data *data)
{
	int	aux;

	pthread_mutex_lock(&data->killer);
	aux = data->death;
	pthread_mutex_unlock(&data->killer);
	return (aux);
}

void	ft_set_death_true(t_data *data)
{
	pthread_mutex_lock(&data->killer);
	data->death = 1;
	pthread_mutex_unlock(&data->killer);
}

void	ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		ft_message(philo, 0);
		pthread_mutex_lock(philo->fork_l);
		ft_message(philo, 0);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		ft_message(philo, 0);
		pthread_mutex_lock(philo->fork_r);
		ft_message(philo, 0);
	}
}
