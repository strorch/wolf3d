/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:58:30 by mstorcha          #+#    #+#             */
/*   Updated: 2018/09/15 20:58:45 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// static void  readf(int argc, char **argv)
// {
//  (void)argc;
//  (void)argv;
// }

t_map   read_map(int argc, char **argv)
{
  t_map   map;
  int     **key_map;
  int     i;
  int     j;

  (void)argc;
  (void)argv;
  key_map = (int **)ft_memalloc(sizeof(int *) * H);
  i = -1;
  while (++i < H)
  {
    key_map[i] = (int *)ft_memalloc(sizeof(int) * W);
    j = -1;
    while (++j < W)
    {
      key_map[i][j] = worldMap[i][j];
    }
  }
  map.h = H;
  map.w = W;
  map.keys = key_map;
  return (map);
}
