/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:11:49 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/12 15:03:17 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

//SUFFISANT POUR VERIF MAP CLOSE ?
int	ft_around(char **map, int i, int j)
{
	int	result;

	if (j == 0 || i == 0)
		return (0);
	else if (!map[i][j + 1])
		return (0);
	else if (!map[i + 1])
		return (0);
	result = ft_clist(map[i][j + 1]);
	if (result != 1 && result != 2)
		return (0);
	result = ft_clist(map[i][j - 1]);
	if (result != 1 && result != 2)
		return (0);
	result = ft_clist(map[i + 1][j]);
	if (result != 1 && result != 2)
		return (0);
	result = ft_clist(map[i - 1][j]);
	if (result != 1 && result != 2)
		return (0);
	return (1);
}

int	ft_coord_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || ft_clist(map[i][j]) == 2)
			{
				if (!ft_around(map, i, j))
					return (ft_return("open map"));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_struct(t_map *map)
{
	if (!map->no_texture || !map->so_texture)
		return (ft_return("no or so texture invalid"));
	if (!map->we_texture || !map->ea_texture)
		return (ft_return("we or ea texture invalid"));
	if (!map->floor || !map->ceiling)
		return (ft_return("floor or ceiling rgb invalid"));
	if (!map->strmap)
		return (ft_return("map array not created"));
	return (1);
}

int	ft_check_format(t_map map)
{
	if (!ft_check_extension(map.map_name, ".cub"))
		return (ft_return("extension"));
	if (!ft_check_extension(map.no_texture, ".xpm"))
		return (ft_return("wrong extension no"));
	if (!ft_check_extension(map.so_texture, ".xpm"))
		return (ft_return("wrong extension so"));
	if (!ft_check_extension(map.we_texture, ".xpm"))
		return (ft_return("wrong extension we"));
	if (!ft_check_extension(map.ea_texture, ".xpm"))
		return (ft_return("wrong extension ea"));
	return (1);
}

int	ft_parsing(t_data *data)
{
	if (!ft_check_struct(&data->data_map))
		return (ft_free_init(&data->data_map, NULL));
	if (!ft_check_format(data->data_map))
		return (ft_free_init(&data->data_map, NULL));
	if (!ft_check_char(data->data_map.strmap))
		return (ft_free_init(&data->data_map, NULL));
	if (!ft_check_closed(data->data_map.strmap))
		return (ft_free_init(&data->data_map, NULL));
	if (!ft_coord_check(data->data_map.strmap))
		return (ft_free_init(&data->data_map, NULL));
	ft_imap(&data->data_map);
	return (1);
}
