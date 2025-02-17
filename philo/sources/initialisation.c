/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:16:10 by dancel            #+#    #+#             */
/*   Updated: 2025/02/17 17:17:05 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(int i, t_data *data)
{
	data->p[i] = malloc(sizeof(t_philo));
	if (!data->p[i])
		return (exit_philo("Error : malloc failed\n", data), 0);
	data->p[i]->id = i;
	data->p[i]->n_meal = 0;
	data->p[i]->n_fork = 0;
	data->p[i]->is_alive = 1;
	data->p[i]->is_hungry = 1;
	data->p[i]->last_meal = data->start_time;
	data->p[i]->data = data;
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
		data->n_e = -1;
		if (i == 5)
			data->n_e = temp;
	}
	return (ac == 5 || ac == 6);
}

int	init_data(int ac, char **av, t_data *data)
{
	int				i;

	i = -1;
	data->thread = NULL;
	if (!parsing(ac, av, data))
		return (exit_philo("Error : invalid input\n", data), 0);
	data->start_time = get_time();
	data->thread = malloc(sizeof(pthread_t) * data->n_p);
	data->p = malloc(sizeof(t_philo) * data->n_p);
	if (!data->thread || !data->p)
		return (exit_philo("Error : malloc failed\n", data), 0);
	while (++i < data->n_p)
	{
		if (!create_philo(i, data))
			return (exit_philo("Error : malloc failed\n", data), 0);
		if (pthread_create(&data->thread[i], NULL, routine, data->p[i]))
			return (exit_philo("Error : pthread_create failed\n", data), 0);
		data->p[i]->thread = data->thread[i];
	}
	return (1);
}
