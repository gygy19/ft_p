/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DownloadPartProtocolMessage.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 10:06:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 10:06:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static char	*readsocketfilecontent(t_client *client, size_t size)
{
	char    *part;
	char    buffer[4096 + 1];
	size_t  currentRet;
	size_t  ret;

	currentRet = 0;
	ret = 0;
	part = ft_strnew(size + 1);
	while (currentRet < size)
	{
		ret = recv(client->fd, buffer,\
			(size - currentRet) < 4096 ? (size - currentRet) : 4096, 0);
		buffer[ret] = '\0';
		ft_memcpy(part + currentRet, buffer, ret);
		currentRet += ret;
	}
	return (part);
}

BOOLEAN		processReceivedUploadPartProtocolMessage(t_socket_server *server,\
  t_client *client, char *message)
{
	char    **split;
	size_t  size;
	char    *part;

	(void)server;
	split = ft_split_string(message, "|");
	if (array_length(split) != 1)
		return (false);
	if (client->download == NULL)
		return (false);
	size = ft_atoi(split[0]);
	part = readsocketfilecontent(client, size);
	downloadpart(client->download, part, size);
	ft_printf("Download of \"%s\" [%d%%/100%%]\n", client->download->dest,\
		(100 * client->download->offset) / client->download->size);
	if (client->download->currentPart < client->download->maxPart)
		client->send(client,\
			client->serialize("%c%d", 14, client->download->currentPart));
	else
		ft_printf("file downladed complet\n");
	free_array(split);
	return (true);
}
