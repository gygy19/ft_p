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
	t_protocolmessage				*protocolmessage;

	packetid = message[0];
	finalmessage = ft_strsub(message, 1, ft_strlen(message));
	protocolmessage = (t_protocolmessage*)client->messagesreceivedmap->get(\
		client->messagesreceivedmap, packetid);
	if (protocolmessage != NULL)
	{
		if (protocolmessage->reprintprompt)
			ft_putstr("\033[u\033[K");
		protocolmessage->execute(client, finalmessage);
		if (protocolmessage->reprintprompt)
			reprint_line(client, true);
	}
	else
	{
		ft_printf("{color70}Message ({color149}%d%s\n",\
			packetid, "{reset}{color70}) {red}not handle{reset}");
	}
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
}
