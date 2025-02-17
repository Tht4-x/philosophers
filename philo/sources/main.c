/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:53:21 by dancel            #+#    #+#             */
/*   Updated: 2025/02/17 17:23:31 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(char *s, t_data *data)
{
	int	i;

	i = -1;
	while (data->p && data->p[++i]) //si malloc data p fail, thread not free
	{
		pthread_join(data->p[i]->thread, NULL);
		free(data->p[i]);
	}
	free(data->p);
	free(data->thread);
	free(data);
	write(2, s, ft_strlen(s));
}

void	log_print(int id, int action)
{
	int		time;
	char	*s;

	time = (int)get_time();
	if (action == 0)
		s = "has taken a fork";
	if (action == 1)
	{
		printf("%d %d has taken a fork\n", time, id);
		s = "is eating";
	}
	if (action == 2)
		s = "is sleeping";
	if (action == 3)
		s = "is thinking";
	if (action == 4)
		s = "died";
	printf("%d %d %s\n", time, id, s);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error : malloc failed\n", 22), 1);
	if (!init_data(ac, av, data))
		return (1);
	printf("%d", data->n_p);
//	ft_debug();
	return (exit_philo("", data), 0);
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