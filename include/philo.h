/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:31:59 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/06 17:44:55 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX 2147483647
#define MIN -2147483648

#define RST    "\033[0m"      /* Reset to default color */
#define RED    "\033[1;31m"   /* Bold Red */
#define G      "\033[1;32m"   /* Bold Green */
#define Y      "\033[1;33m"   /* Bold Yellow */
#define B      "\033[1;34m"   /* Bold Blue */
#define M      "\033[1;35m"   /* Bold Magenta */
#define C      "\033[1;36m"   /* Bold Cyan */
#define W      "\033[1;37m"   /* Bold White */

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*messenger;
	pthread_mutex_t	*killer;
	t_data			*data;
	int				id;
	int				times_eaten;
	int				time_asleep;
	int				time_death;
	int				last_food;
	int				last_eat;
}	t_philo;

typedef struct s_data
{
	t_philo				*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		messenger;
	pthread_mutex_t		killer;
	pthread_t			monitor;
	int					death;
	int					start;
	int					argc;
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					i;
}	t_data;

/*------------------------------ philo.c ------------------------------*/

void	*ft_monitoring(void *i);

/*---------------------------- check_argv.c ---------------------------*/

int		ft_nb_checker(const char *str);
int		ft_check_char(char **numbers);
int		ft_atoi(const char *str);

/*----------------------------- routine.c -----------------------------*/

void	ft_message(t_philo *philo, int x);
void	ft_create_philo(t_data *data);
void	ft_sleep(int time);
int		ft_get_time(void);

/*------------------------------ error.c ------------------------------*/

void	ft_puterrorstr(char *str, t_data *data);
void	ft_free_all(t_data *data);
void	ft_finish(t_data *data);