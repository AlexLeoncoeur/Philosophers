/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:10 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/12 18:26:25 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_think(t_philo *philo)
{
	ft_message(philo, 3);
	if (philo->id % 2)
		ft_sleep(4);
}

void	ft_eat(t_philo *philo)
{
	ft_take_fork(philo);
	ft_message(philo, 1);
	pthread_mutex_lock(philo->time);
	philo->times_eaten++;
	philo->last_eat = ft_get_time() - philo->data->start;
	pthread_mutex_unlock(philo->time);
	ft_sleep(philo->data->time_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	ft_sleep_action(t_philo *philo)
{
	ft_message(philo, 2);
	ft_sleep(philo->data->time_sleep);
}
