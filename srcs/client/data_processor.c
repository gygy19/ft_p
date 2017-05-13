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
	int								packetid;
	char							*finalmessage;
	t_ProtocolMessage				*protocolmessage;

	packetid = message[0];
	finalmessage = ft_strsub(message, 1, ft_strlen(message));
	protocolmessage = (t_ProtocolMessage*)client->messagesReceivedMap->get(\
		client->messagesReceivedMap, packetid);
	if (protocolmessage != NULL)
	{
		if (protocolmessage->reprintPrompt)
			ft_putstr("\033[u\033[K");
		protocolmessage->execute(client, finalmessage);
		if (protocolmessage->reprintPrompt)
			reprint_line(client, true);
	}
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
}
