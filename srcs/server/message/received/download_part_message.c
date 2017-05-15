/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getDownloadPartProtocolMessage.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:28:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/09 17:28:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

BOOLEAN	download_part_message(t_socket_server *server,\
	t_client *client, char *message)
{
	size_t	partid;
	int		savepourcentage;

	(void)server;
	if (client->download == NULL)
		return (false);
	partid = ft_atoi(message);
	(void)partid;
	savepourcentage = (100 * client->download->offset) / client->download->size;
	if (uploadpart(client->download))
	{
		client->send(client, client->serialize("%c%d", 105,\
			client->download->partsize));
		send(client->fd, client->download->part, client->download->partsize, 0);
	}
	return (true);
}
