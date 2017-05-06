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

BOOLEAN   processReceivedDownloadPartProtocolMessage(t_socket_server *server,\
  t_client *client, char *message)
{
  (void)server;
  char    **split;
  size_t  size;
  char    *part;

  split = ft_split_string(message, "|");
  if (array_length(split) != 1)
    return (false);
  if (client->download == NULL)
    return (false);
  size = ft_atoi(split[0]);
  part = ft_strnew(size + 1);
  ft_printf("LA3size:%d to %s\n", size, client->download->dest);
  recv(client->fd, part, size, 0);
  downloadPart(client->download, part, size);
  if (client->download->currentPart != client->download->maxPart)
    client->send(client, client->serialize("%c%d", 14, client->download->currentPart));
  else
    ft_printf("file downladed complet\n");
  //else finished succes message
  free_array(split);
  return (true);
}
