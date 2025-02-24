/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:35:22 by dancel            #+#    #+#             */
/*   Updated: 2025/02/24 16:52:47 by dancel           ###   ########.fr       */
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

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			n_meal;
	int			n_fork;
	int			fork_1;
	int			fork_2;
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
	t_philo			**p;
	pthread_mutex_t	*mutex;
//	pthread_t		*thread;
//	pthread_t		exit;
	int				*fork;
	int				end;
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
void		log_print(int id, int action, t_data *data);
int			main(int argc, char **argv);
/*

# routine.c
# ============================*/
//void		*checker(void *ptr);
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