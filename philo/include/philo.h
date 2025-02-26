/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:35:22 by dancel            #+#    #+#             */
/*   Updated: 2025/02/26 20:14:23 by dancel           ###   ########.fr       */
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

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

# define M_FORK "%d \033[35;1m%d\033[0m \033[34;1mhas taken a fork\033[0m\n"
# define M_EAT "%d \033[35;1m%d\033[0m \033[32;1mis eating\033[0m\n"
# define M_SLEEP "%d \033[35;1m%d\033[0m \033[33;1mis sleeping\033[0m\n"
# define M_THINK "%d \033[35;1m%d\033[0m \033[36;1mis thinking\033[0m\n"
# define M_DIE "%d \033[35;1m%d\033[0m \033[31;1mdied\033[0m\n"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				n_meal;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	time_t			last_meal;
	t_data			*data;
}				t_philo;

typedef struct s_data
{
	time_t			start_time;
	int				n_p;
	time_t			t_d;
	time_t			t_e;
	time_t			t_s;
	int				n_e;
	t_philo			**p;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	global_mutex;
	int				end;
}				t_data;

/*

# initialisation.c
# ============================*/
int			create_philo(int i, t_data *data);
int			parsing(int ac, char **av, t_data *data);
int			init_data(int i, t_data *data);
/*

# main.c
# ============================*/
void		exit_philo(char *s, t_data *data);
void		log_print(int id, int action, t_data *data);
int			main(int argc, char **argv);
/*

# routine.c
# ============================*/
void		check_if_finish(t_data *data);
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