/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:51:05 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/06 14:25:31 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_data(t_philo *philo)
{
	if (!philo)
		return ;
	printf("pipo\n");
	while (philo)
	{
		free(philo);
		philo++;
	}
	free(philo);
}

void	ft_free_all(t_data *data)
{
	data->i = 0;
	while (data->i < data->philo_nb)
		pthread_mutex_destroy(&data->forks[data->i++]);
	free(data->forks);
	//pthread_mutex_destroy(&data->messenger);
	free(data->philosophers);
	/* ft_free_data(data->philosophers); */
	free(data);
}

void	ft_puterrorstr(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	if (data)
		ft_free_all(data);
	exit(1);
}
