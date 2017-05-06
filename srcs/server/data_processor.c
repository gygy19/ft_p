/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:58:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:58:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int			data_processor(t_socket_server *server, t_client *client,\
	char *message)
{
	int								packetId;
	char							*finalmessage;
	t_ProtocolMessage	*protocolMessage;

	packetId = message[0];
	finalmessage = ft_strsub(message, 1, ft_strlen(message));

	protocolMessage = (t_ProtocolMessage*)server->messagesReceivedMap->get(\
		server->messagesReceivedMap, packetId);
	if (protocolMessage != NULL)
	{
		protocolMessage->execute(server, client, finalmessage);
	}
	else
	{
		ft_printf("{color70}Message from [%s:%d] ({color149}%d{reset}{color70}) {red}not handle{reset}\n",\
			inet_ntoa(client->in.sin_addr),\
			ntohs(client->in.sin_port),\
			packetId);
	}
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
	return (0);
}
