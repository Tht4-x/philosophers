/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:53:21 by dancel            #+#    #+#             */
/*   Updated: 2025/02/24 16:56:08 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(char *s, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_p)
	{
		if (data->p && data->p[i] && data->p[i]->thread)
			pthread_join(data->p[i]->thread, NULL);
		if (data->mutex && &data->mutex[i])
			pthread_mutex_destroy(&data->mutex[i]);
//		if (data->p && data->p[i])
//			free(data->p[i]);
	}
	if (data->fork)
		free(data->fork);
	if (data->p)
		free(data->p);
	if (data->mutex && &data->mutex[data->n_p])
		pthread_mutex_destroy(&data->mutex[data->n_p]);
	if (data->mutex)
		free(data->mutex);
//	if (data->thread) //a verifier
//		free(data->thread);
	free(data);
	write(2, s, ft_strlen(s));
}

void	log_print(int id, int action, t_data *data)
{
	int		time;
	char	*s;

	pthread_mutex_lock(&data->mutex[data->n_p]);
	if (data->end)
		return ;
	time = (int)get_time() - data->start_time;
	if (action == FORK)
		s = "\033[34;1mhas taken a fork\033[0m";
	if (action == EAT)
	{
		printf("%d \033[35;1m%d\033[0m \033[34;1mhas taken a fork\033[0m\n"\
			, time, id);
		s = "\033[32;1mis eating\033[0m";
	}
	if (action == SLEEP)
		s = "\033[33;1mis sleeping\033[0m";
	if (action == THINK)
		s = "\033[36;1mis thinking\033[0m";
	if (action == DIE)
		s = "\033[31;1mdied\033[0m";
	printf("%d \033[35;1m%d\033[0m %s\n", time, id, s);
	pthread_mutex_unlock(&data->mutex[data->n_p]);
}

int	main(int ac, char **av)
{
	t_data		*data;
//	pthread_t	exit;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error : malloc failed\n", 22), 1);
	if (!init_data(ac, av, data))
		return (1);
//	exit = data->exit;
	while (!data->end)
		usleep(100);
	exit_philo("", data);
//	pthread_join(exit, NULL);
	return (0);
}

/*
mettre les mutex dans les philos avec adresse du 2e mutex ?
	->echanger gauche et droite
faire les threads dans les philo
s'arrete un moment sans ne plus rien afficher
plusieurs messages s'affichent en meme temps comme 2x died

Si deux philosophes veulent la meme fourchette, priorite au plus petit ?
philo impairs commencent par reflechir

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