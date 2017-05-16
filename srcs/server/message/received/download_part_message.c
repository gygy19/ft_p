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

	(void)server;
	if (client->upload == NULL)
		return (false);
	partid = ft_atoi(message);
	(void)partid;
	if (uploadpart(client->upload))
	{
		ft_printf("Upload of \"%s\" [%d%%/100%%]\n", client->upload->filename,\
		(100 * client->upload->offset) / client->upload->size);
		client->send(client, client->serialize("%c%d", 104,\
			client->upload->partsize));
		send(client->fd, client->upload->part, client->upload->partsize, 0);
	}
	return (true);
}
