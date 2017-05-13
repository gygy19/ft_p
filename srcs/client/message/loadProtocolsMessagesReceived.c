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

void	loadprotocolsmessagesreceived(t_socket_client *client)
{
	int	i;

	i = 0;
	(void)i;
	(void)client;
	client->messagesReceivedMap = newintegerhashmap(10);
	while (i < ARRAY_RECEIVED_MESSAGES_SIZE)
	{
		ft_printf("%s, %d\n", arrayprotocolmessagesreceived[i].name,\
			arrayprotocolmessagesreceived[i].key);
		client->messagesReceivedMap->add(client->messagesReceivedMap,\
			arrayprotocolmessagesreceived[i].key,\
			&arrayprotocolmessagesreceived[i]);
		i++;
	}
}
