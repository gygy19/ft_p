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
	client->messagessendmap = newstringhashmap(10);
	while (i < AR_CMD_SIZE)
	{
		client->messagessendmap->add(client->messagessendmap,\
			g_arrayprotocolmessagessend[i].name,\
			&g_arrayprotocolmessagessend[i]);
		i++;
	}
}
