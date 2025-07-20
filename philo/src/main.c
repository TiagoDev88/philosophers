/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/20 12:20:27 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("%s", ERR_ARGS), 0);
	if (!only_num(argv))
		return (printf("%s", ERR_ONLY_NUM), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv))
		return (1);
	if (!init_all(&data, argc, argv))
		return (1);

	return (0);
}
