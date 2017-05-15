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

int	data_processor(t_socket_server *server, t_client *client, char *message)
{
	int					packetid;
	char				*finalmessage;
	t_protocolmessage	*protocolmessage;

	packetid = message[0];
	finalmessage = ft_strsub(message, 1, ft_strlen(message));
	protocolmessage = (t_protocolmessage*)server->messagesreceivedmap->get(\
		server->messagesreceivedmap, packetid);
	if (protocolmessage != NULL)
	{
		protocolmessage->execute(server, client, finalmessage);
	}
	else
	{
		ft_printf("{color70}Message from [%s:%d] ({color149}%d%s\n",\
			inet_ntoa(client->in.sin_addr),\
			ntohs(client->in.sin_port),\
			packetid, "{reset}{color70}) {red}not handle{reset}");
	}
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
	return (0);
}
