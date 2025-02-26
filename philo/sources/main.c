/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:53:21 by dancel            #+#    #+#             */
/*   Updated: 2025/02/26 22:00:59 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(char *s, t_data *data)
{
	int	i;

	pthread_mutex_unlock(&data->global_mutex);
	pthread_mutex_destroy(&data->global_mutex);
	i = -1;
	while (++i < data->n_p)
	{
		pthread_mutex_unlock(&data->mutex[i]);
		pthread_mutex_destroy(&data->mutex[i]);
	}
	i = -1;
	while (++i < data->n_p)
	{
		if (data->p && data->p[i] && data->p[i]->thread)
			pthread_join(data->p[i]->thread, NULL);
		if (data->p && data->p[i])
			free(data->p[i]);
	}
	if (data->p)
		free(data->p);
	if (data->mutex)
		free(data->mutex);
	free(data);
	write(2, s, ft_strlen(s));
}

void	log_print(int id, int action, t_data *data)
{
	int		time;

	pthread_mutex_lock(&data->global_mutex);
	if (data->end)
	{
		pthread_mutex_unlock(&data->global_mutex);
		return ;
	}
	time = (int)get_time() - data->start_time;
	if (action == FORK)
		printf(M_FORK, time, id + 1);
	if (action == EAT)
		printf(M_FORK M_EAT, time, id + 1, time, id + 1);
	if (action == SLEEP)
		printf(M_SLEEP, time, id + 1);
	if (action == THINK)
		printf(M_THINK, time, id + 1);
	if (action == DIE)
		printf(M_DIE, time, id + 1);
	pthread_mutex_unlock(&data->global_mutex);
}

static void	check_if_finish(t_data *data)
{
	int	i;

	i = -1;
	while (data->p[++i])
	{
		if (get_time() - data->p[i]->last_meal >= data->t_d)
		{
			log_print(i, DIE, data);
			pthread_mutex_lock(&data->global_mutex);
			data->end = 1;
			pthread_mutex_unlock(&data->global_mutex);
			return ;
		}
	}
	i = -1;
	while (data->p[++i])
	{
		if (data->p[i]->n_meal < data->n_e)
			return ;
	}
	pthread_mutex_lock(&data->global_mutex);
	data->end = 2;
	pthread_mutex_unlock(&data->global_mutex);
}

static int	parsing(int ac, char **av, t_data *data)
{
	int			i;
	long long	temp;

	i = 0;
	while (av[++i])
	{
		if (!ft_strisdigit(av[i]))
			return (0);
		temp = ft_atoll(av[i]);
		if (temp > INT_MAX || temp < 0)
			return (0);
		if (i == 1)
			data->n_p = temp;
		if (i == 2)
			data->t_d = temp;
		if (i == 3)
			data->t_e = temp;
		if (i == 4)
			data->t_s = temp;
		data->n_e = INT_MAX;
		if (i == 5)
			data->n_e = temp;
	}
	return (ac == 5 || ac == 6);
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error : malloc failed\n", 22), 1);
	if (!parsing(ac, av, data))
		return (free(data), write(2, "Error : invalid input\n", 22), 0);
	if (data->n_e == 0 || data->n_p == 0)
		return (free(data), 0);
	if (!init_data(-1, data))
		return (1);
	while (!data->end)
		check_if_finish(data);
	exit_philo("", data);
	return (0);
}

/*
meurs si impair
	ceux qui mangent doivent alterner
	ne prend pas premiere fourchette si la 2e est deja prise
	ou prends les 2 fourchettes d'un coup
	ou repose fourchette 

TEST
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die. 
Test 5 800 200 200 7. No die and win.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die

ARG
	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat

Fonctions
	memset, printf, malloc, free, write,
	usleep, gettimeofday, pthread_create,
	pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock,
	pthread_mutex_unlock

Message
	◦timestamp_in_ms X has taken a fork
	◦timestamp_in_ms X is eating
	◦timestamp_in_ms X is sleeping
	◦timestamp_in_ms X is thinking
	◦timestamp_in_ms X died
*/