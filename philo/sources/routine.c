/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:14:46 by dancel            #+#    #+#             */
/*   Updated: 2025/02/26 20:25:05 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_if_finish(t_data *data)
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

int	waiting_routine(time_t timer, t_philo *p)
{
	time_t	stop;

	stop = get_time() + timer;
	while (get_time() < stop)
		usleep(100);
	return (p->data->end);
}

void	*routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	if (p->id % 2 == 1)
		usleep (3000);
	while (!p->data->end)
	{
		pthread_mutex_lock(p->fork_1);
		if (p->data->end)
			break ;
		log_print(p->id, FORK, p->data);
		pthread_mutex_lock(p->fork_2);
		if (p->data->end)
			break ;
		log_print(p->id, EAT, p->data);
		p->last_meal = get_time();
		p->n_meal++;
		if (waiting_routine(p->data->t_e, p))
			break ;
		log_print(p->id, SLEEP, p->data);
		pthread_mutex_unlock(p->fork_2);
		pthread_mutex_unlock(p->fork_1);
		if (waiting_routine(p->data->t_s, p))
			break ;
		log_print(p->id, THINK, p->data);
	}
	return (NULL);
}
