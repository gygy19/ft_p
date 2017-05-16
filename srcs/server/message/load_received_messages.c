/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_received_messages.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:13:18 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 18:13:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	load_received_messages(t_socket_server *server)
{
	int	i;

	i = 0;
	server->messagesreceivedmap = newintegerhashmap(10);
	while (i < AR_RCV_SIZE)
	{
		server->messagesreceivedmap->add(server->messagesreceivedmap,\
			g_arrayprotocolmessagesreceived[i].key,\
			&g_arrayprotocolmessagesreceived[i]);
		i++;
	}
}
