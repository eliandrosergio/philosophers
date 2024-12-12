/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:36 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	deinit_structs(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_mutex_destroy(&state->p_philos[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&state->p_dead->mutex);
	free(state->p_philos);
	free(state->p_forks);
	free(state->p_dead);
}

int	init(t_state *state, int argc, char **argv)
{
	if (init_arguments(state, argc, argv) == -1 || init_structs(state) == -1)
		return (-1);
	if (init_fork_mutexes(state) == -1)
		return (-1);
	if (init_philo_mutexes(state) == -1)
		return (-1);
	if (init_dead_mutex(state) == -1)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_state		*state;
	pthread_t	*philo_threads;

	if (args_check(argc, argv) == -1)
		return (-1);
	state = (t_state *) malloc(ft_atoi(argv[1]) * sizeof(t_state));
	if (state == NULL)
		return (printf("malloc of state failed.\n"), -1);
	if (init(state, argc, argv) == -1)
		return (-1);
	if (init_threads(state, &philo_threads) == -1)
		return (-1);
	if (create_threads(state, philo_threads) == -1)
		return (-1);
	while (is_program_end(state) == 0)
	{
		ft_wait(9000);
	}
	wait_for_threads(state, philo_threads);
	deinit_structs(state);
	free(state);
	free(philo_threads);
	return (0);
}
