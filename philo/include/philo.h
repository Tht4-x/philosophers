/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:35:22 by dancel            #+#    #+#             */
/*   Updated: 2025/02/17 17:23:41 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			n_meal;
	int			n_fork;
	int			is_alive;
	int			is_hungry;
	time_t		last_meal;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	time_t			start_time;
	int				n_p;
	int				t_d;
	int				t_e;
	int				t_s;
	int				n_e;
	pthread_t		*thread;
	t_philo			**p;
	int				*fork;
//	pthread_mutex_t	**fork_mut;
//	int				*fork_bool;
}				t_data;

/*

# initialisation.c
# ============================*/
int			create_philo(int i, t_data *data);
int			parsing(int ac, char **av, t_data *data);
int			init_data(int ac, char **av, t_data *data);
/*

# main.c
# ============================*/
void		exit_philo(char *s, t_data *data);
void		log_print(int id, int action);
int			main(int argc, char **argv);
/*

# routine.c
# ============================*/
void		*routine(void *data);
/*

# utils_1.c
# ============================*/
size_t		ft_strlen(const char *s);
int			ft_strisdigit(const char *nb);
long long	ft_atoll(const char *nptr);
time_t		get_time(void);
void		ft_debug(void);

#endif