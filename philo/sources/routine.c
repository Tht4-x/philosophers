/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:14:46 by dancel            #+#    #+#             */
/*   Updated: 2025/02/17 17:15:04 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//gerer le cas du dernier philosophe
//gerer si 1 philo decede
//gerer les mutex
void	*routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	while (1)
	{
		usleep(1);
		if (get_time() - p->last_meal >= p->data->t_d)
		{
			p->is_alive = 0;
			log(p->id, 4);
			break ;
		}
		if (p->n_fork == 0 && p->data->fork[p->id + 1 - p->id % 2] == 0 && p->is_hungry == 1)
		{
			p->data->fork[p->id + 1 - p->id % 2] == 1;
			p->n_fork = 1;
			log(p->id, 0);
		}
		if (p->n_fork == 1 && p->data->fork[p->id + p->id % 2] == 0)
		{
			p->data->fork[p->id + p->id % 2] == 1;
			p->n_fork = 2;
			p->last_meal = get_time();
			p->n_meal++;
			p->is_hungry = 0;
			log(p->id, 1);
		}
		if (get_time() - p->last_meal > p->data->t_e)
		{
			p->n_fork = 0;
			p->data->fork[p->id] = 0;
			p->data->fork[p->id + 1] = 0;
			log(p->id, 2);
		}
		if (get_time() - p->last_meal > p->data->t_e + p->data->t_s)
		{
			p->is_hungry = 1;
			log(p->id, 3);
		}
	}
	return (NULL);
}