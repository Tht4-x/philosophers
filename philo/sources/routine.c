/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:14:46 by dancel            #+#    #+#             */
/*   Updated: 2025/02/24 16:52:12 by dancel           ###   ########.fr       */
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
			data->end = 1;
			return ;
		}
	}
	i = -1;
	while (data->p[++i])
	{
		if (data->p[i]->n_meal < data->n_e)
			return ;
	}
	data->end = 2;
}

// void	*checker(void *ptr)
// {
// 	t_data	*data;

// 	data = ptr;
// 	while (!data->end)
// 		usleep(1);
// //	pthread_mutex_lock(&data->mutex[data->n_p]);
// 	exit_philo("", data);
// 	return (NULL);
// }

//securiser les mutex ?
void	*routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	if (p->id % 2 == 1)
		usleep (3000);
	while (!p->data->end)
	{
		if (get_time() - p->last_meal >= p->data->t_d && !p->data->end)
		{
			log_print(p->id, DIE, p->data);
			p->data->end = 1;
			break ;
		}
		if (p->n_fork == 0 && !p->data->fork[p->fork_1] && p->is_hungry == 2)
		{
			pthread_mutex_lock(&p->data->mutex[p->fork_1]);
			log_print(p->id, FORK, p->data);
			p->data->fork[p->fork_1] = 1;
			p->n_fork = 1;
		}
		if (p->n_fork == 1 && !p->data->fork[p->fork_2])
		{
			pthread_mutex_lock(&p->data->mutex[p->fork_2]);
			log_print(p->id, EAT, p->data);
			p->data->fork[p->fork_2] = 1;
			p->n_fork = 2;
			p->last_meal = get_time();
			p->n_meal++;
			p->is_hungry = 0;
			check_if_finish(p->data);
		}
		if (p->is_hungry == 0 && get_time() - p->last_meal > p->data->t_e)
		{
			log_print(p->id, SLEEP, p->data);
			p->n_fork = 0;
			p->data->fork[p->fork_2] = 0;
			pthread_mutex_unlock(&p->data->mutex[p->fork_2]);
			p->data->fork[p->fork_1] = 0;
			pthread_mutex_unlock(&p->data->mutex[p->fork_1]);
			p->is_hungry = 1;
		}
		if (p->is_hungry == 1 && get_time() - p->last_meal > p->data->t_e + p->data->t_s)
		{
			log_print(p->id, THINK, p->data);
			p->is_hungry = 2;
		}
	}
//	printf("EXIT %d\n", p->id);
	return (NULL);
}
