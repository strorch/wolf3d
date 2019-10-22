/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:50:17 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/22 19:50:18 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	exit_message(const char *str)
{
	ft_putendl(str);
	exit(0);
}

void	print_usage(void)
{
	ft_putendl("Usage:");
	ft_putendl("\t./wolf3d maps/1.m");
	exit(1);
}
