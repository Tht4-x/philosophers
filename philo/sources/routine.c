/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:14:46 by dancel            #+#    #+#             */
/*   Updated: 2025/02/27 23:09:21 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_data *data)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&data->global_mutex);
	if (data->end)
		end = 1;
	pthread_mutex_unlock(&data->global_mutex);
	return (end);
}

static int	waiting_routine(time_t timer, t_philo *p)
{
	time_t	stop;

	if (timer == PHILOSOPHIZE)
		timer = (p->data->t_d - (get_time() - p->last_meal) - p->data->t_e) / 2;
	stop = get_time() + timer;
	while (get_time() < stop)
		usleep(100);
	return (check_end(p->data));
}

static int	routine_loop(t_philo *p)
{
	pthread_mutex_lock(p->fork_1);
	if (check_end(p->data))
		return (0);
	log_print(p->id, FORK, p->data);
	pthread_mutex_lock(p->fork_2);
	if (check_end(p->data))
		return (0);
	log_print(p->id, EAT, p->data);
	p->last_meal = get_time();
	p->n_meal++;
	if (waiting_routine(p->data->t_e, p))
		return (0);
	log_print(p->id, SLEEP, p->data);
	pthread_mutex_unlock(p->fork_2);
	pthread_mutex_unlock(p->fork_1);
	if (waiting_routine(p->data->t_s, p))
		return (0);
	log_print(p->id, THINK, p->data);
	waiting_routine(PHILOSOPHIZE, p);
	return (1);
}

void	*routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	if (p->id % 2 == 1)
		waiting_routine(PHILOSOPHIZE, p);
	while (1)
	{
		if (!routine_loop(p))
			break ;
	}
	pthread_mutex_unlock(&p->data->global_mutex);
	return (NULL);
}
