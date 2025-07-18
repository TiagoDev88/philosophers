/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:55:54 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/18 22:10:03 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo <num_philos> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [<must_eat>]\n");
		return (1);
	}
	// se der erro a iniciar as structsm dar erro,
	// criar os philos, caso seja diferente de 0 dar erro
	// comecar a simulacao
	// limpar tudo
	return (0);
}
