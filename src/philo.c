/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:30:24 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/06 17:48:56 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_monitoring(void *x)
{
	t_data	*data;
	int		philos_sick;
	int		i;

	philos_sick = 0;
	data = (t_data *)x;
	i = 0;
	while (philos_sick != data->philo_nb)
	{
		if (i == data->philo_nb - 1)
			i = 0;
		if (data->philosophers[i].times_eaten == data->must_eat)
			philos_sick++;
		else if (((ft_get_time() - data->start) - data->philosophers[i].last_eat) >= data->time_die)
		{
			pthread_mutex_lock(&data->killer);
			data->death = 1;
			pthread_mutex_unlock(&data->killer);
			ft_message(&data->philosophers[i], 4);
			break ;
		}
		i++;
	}
	return (data->death = 1, NULL);
}

static void	ft_init_mutex(t_data *data)
{
	data->i = 0;
	while (data->i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[data->i], NULL);
		data->i++;
	}
	pthread_mutex_init(&data->messenger, NULL);
	pthread_mutex_init(&data->killer, NULL);
}

static void	ft_init_philo(t_data *data)
{
	data->i = 0;
	while (data->i < data->philo_nb)
	{
		data->philosophers[data->i].times_eaten = 0;
		data->philosophers[data->i].time_asleep = 0;
		data->philosophers[data->i].last_food = 0;
		data->philosophers[data->i].last_eat = 0;
		data->philosophers[data->i].time_death = data->time_die;
		data->philosophers[data->i].messenger = &data->messenger;
		data->philosophers[data->i].killer = &data->killer;
		data->philosophers[data->i].data = data;
		data->philosophers[data->i].id = data->i;
		data->philosophers[data->i].fork_l = data->forks[data->i % 5];
		if ((data->i + 1) == data->philo_nb)
			data->philosophers[data->i].fork_r = data->forks[0];
		else
			data->philosophers[data->i].fork_r = data->forks[data->i % 5 + 1];
		data->i++;
	}
}

static void	ft_prepare_struct(int argc, char **argv, t_data *data)
{
	t_philo				*philosophers;
	pthread_mutex_t		*forks;

	philosophers = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	forks = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philosophers || !forks)
		ft_puterrorstr("Error: Could not create struct\n", data);
	data->argc = argc;
	data->philo_nb = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->must_eat = ft_atoi(argv[5]);
	data->death = 0;
	data->philosophers = philosophers;
	data->forks = forks;
	pthread_mutex_init(&data->killer, NULL);
	ft_init_mutex(data);
	ft_init_philo(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_puterrorstr("Error\n", NULL);
	if (argc != 6)
		ft_puterrorstr("Error: Wrong number of arguments\n", NULL);
	if (ft_check_char(&argv[1]) == 1 || ft_nb_checker(argv[1]) == 1
		|| ft_nb_checker(argv[2]) == 1 || ft_nb_checker(argv[3]) == 1
		|| ft_nb_checker(argv[4]) == 1 || ft_nb_checker(argv[5]) == 1)
		ft_puterrorstr("Error: Argument is not valid\n", NULL);
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[5]) == 0)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		ft_puterrorstr("Error: Timers must be above 60ms\n", NULL);
	ft_prepare_struct(argc, argv, data);
	ft_create_philo(data);
	return (ft_free_all(data), 0);
}
