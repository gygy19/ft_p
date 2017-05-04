/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadProtocolsMessagesReceived.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:13:18 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 18:13:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void loadProtocolsMessagesReceived(t_socket_server *server)
{
  int i;

  i = 0;
  server->messagesReceivedMap = newintegerhashmap(10);
  while (i < ARRAY_RECEIVED_MESSAGES_SIZE)
  {
    ft_printf("%s, %d\n", arrayProtocolMessagesReceived[i].name, arrayProtocolMessagesReceived[i].key);
    server->messagesReceivedMap->add(server->messagesReceivedMap, arrayProtocolMessagesReceived[i].key, &arrayProtocolMessagesReceived[i]);
    i++;
  }
}
