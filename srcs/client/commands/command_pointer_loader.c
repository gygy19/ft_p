/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLoader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:32:01 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 15:32:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	load_command_pointer(t_socket_client *client)
{
	int	i;

	i = 0;
	client->commandsmap = newstringhashmap(10);
	while (i < AR_CMD_SIZE)
	{
		ft_printf("%s, %d\n", g_arrayclientcommands[i].name,\
			g_arrayclientcommands[i].key);
		client->commandsmap->add(client->commandsmap,\
			g_arrayclientcommands[i].name, &g_arrayclientcommands[i]);
		i++;
	}
}
