/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:14:46 by dancel            #+#    #+#             */
/*   Updated: 2025/02/26 21:54:18 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	waiting_routine(time_t timer, t_philo *p)
{
	time_t	stop;
	int		end;

	stop = get_time() + timer;
	while (get_time() < stop)
		usleep(100);
	pthread_mutex_lock(&p->data->global_mutex);
	end = p->data->end;
	pthread_mutex_unlock(&p->data->global_mutex);
	return (end);
}

static int	routine_loop(t_philo *p)
{
	//verifier si impair que la 2e fourchette n'est pas deja prise
	pthread_mutex_lock(p->fork_1);
	pthread_mutex_lock(&p->data->global_mutex);//
	if (p->data->end)
		return (0);
	pthread_mutex_unlock(&p->data->global_mutex);//
	log_print(p->id, FORK, p->data);
	pthread_mutex_lock(p->fork_2);
	pthread_mutex_lock(&p->data->global_mutex);//
	if (p->data->end)
		return (0);
	pthread_mutex_unlock(&p->data->global_mutex);//
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
	return (1);
}

void	*routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	if (p->id % 2 == 1)
		usleep (3000);
	while (1)
	{
		if (!routine_loop(p))
			break ;
	}
	pthread_mutex_unlock(&p->data->global_mutex);
	return (NULL);
}
