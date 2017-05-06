/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:15:28 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:15:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void		data_processor(t_socket_client *client, char *message)
{
	int								packetId;
	char							*finalmessage;
	t_ProtocolMessage	*protocolMessage;

	ft_putstr("\033[u");
	ft_putstr("\033[K");
	packetId = message[0];
	finalmessage = ft_strsub(message, 1, ft_strlen(message));
	protocolMessage = (t_ProtocolMessage*)client->messagesReceivedMap->get(client->messagesReceivedMap, packetId);
	if (protocolMessage != NULL)
		protocolMessage->execute(client, finalmessage);
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
	ft_putstr("\033[s");
	reprint_line(client);
}
