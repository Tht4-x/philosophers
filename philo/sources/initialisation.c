/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:16:10 by dancel            #+#    #+#             */
/*   Updated: 2025/02/27 23:08:32 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo(int i, t_data *data)
{
	data->p[i] = malloc(sizeof(t_philo));
	if (!data->p[i])
		return (exit_philo("Error : malloc failed\n", data), 0);
	data->p[i]->id = i;
	data->p[i]->n_meal = 0;
	data->p[i]->fork_1 = &data->mutex[i + 1 - i % 2];
	data->p[i]->fork_2 = &data->mutex[i + i % 2];
	if (i == data->n_p - 1 && i % 2 == 0)
		data->p[i]->fork_1 = &data->mutex[0];
	else if (i == data->n_p - 1 && i % 2 == 1)
		data->p[i]->fork_2 = &data->mutex[0];
	data->p[i]->last_meal = data->start_time;
	data->p[i]->data = data;
	if (pthread_create(&data->p[i]->thread, NULL, routine, data->p[i]))
		return (exit_philo("Error : pthread_create failed\n", data), 0);
	return (1);
}

int	init_data(int i, t_data *data)
{
	data->mutex = NULL;
	data->end = 0;
	data->start_time = get_time();
	data->p = malloc(sizeof(t_philo) * data->n_p);
	data->mutex = malloc(sizeof(pthread_mutex_t) * (data->n_p));
	if (!data->p || !data->mutex)
		return (exit_philo("Error : malloc failed\n", data), 0);
	while (++i < data->n_p)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (exit_philo("Error : pthread_mutex_init failed\n", data), 0);
	}
	if (pthread_mutex_init(&data->global_mutex, NULL))
		return (exit_philo("Error : pthread_mutex_init failed\n", data), 0);
	i = -1;
	while (++i < data->n_p)
	{
		if (!create_philo(i, data))
			return (0);
	}
	return (1);
}

int	parsing(int ac, char **av, t_data *data)
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
