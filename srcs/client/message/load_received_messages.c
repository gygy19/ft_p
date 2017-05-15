/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadProtocolMessagesReceived.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 20:08:18 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 20:08:19 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	load_received_messages(t_socket_client *client)
{
	int	i;

	i = 0;
	(void)i;
	(void)client;
	client->messagesreceivedmap = newintegerhashmap(10);
	while (i < AR_RCV_SIZE)
	{
		ft_printf("%s, %d\n", g_arrayprotocolmessagesreceived[i].name,\
			g_arrayprotocolmessagesreceived[i].key);
		client->messagesreceivedmap->add(client->messagesreceivedmap,\
			g_arrayprotocolmessagesreceived[i].key,\
			&g_arrayprotocolmessagesreceived[i]);
		i++;
	}
}
