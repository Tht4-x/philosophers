/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:53:21 by dancel            #+#    #+#             */
/*   Updated: 2025/02/27 23:08:13 by dancel           ###   ########.fr       */
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

	if (check_end(data))
		return ;
	pthread_mutex_lock(&data->global_mutex);
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

int	check_if_finish(t_data *data)
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
			return (1);
		}
	}
	i = -1;
	while (data->p[++i])
	{
		if (data->p[i]->n_meal < data->n_e)
			return (0);
	}
	pthread_mutex_lock(&data->global_mutex);
	data->end = 2;
	pthread_mutex_unlock(&data->global_mutex);
	return (1);
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
	while (!check_if_finish(data))
		usleep(100);
	exit_philo("", data);
	return (0);
}

/*
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