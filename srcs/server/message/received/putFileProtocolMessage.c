/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putFileProtocolMessage.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 09:36:47 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 09:36:49 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

BOOLEAN   processReceivedputFileProtocolMessage(t_socket_server *server,\
  t_client *client, char *message)
{
  (void)server;
  char      **split;
  t_upload  *download;
  char      *infos;
  char      *dest;

  split = ft_split_string(message, "|");
  if (array_length(split) != 3)
    return (false);
  if (client->pwd[ft_strlen(client->pwd) - 1] == '/')
    dest = ft_strjoin(client->pwd, split[0]);
  else
    dest = ft_dstrjoin(ft_strjoin(client->pwd, "/"), split[0], 1);
  infos = ft_sprintf("%s|%d|%s", split[1], ft_atoi(split[2]), dest);//'path|size|dest'
  download = loadnewDownload(split[0], infos);
  if (download != NULL)
  {
    client->download = download;
    client->send(client, client->serialize("%c%d", 14, client->download->currentPart));
  }
  //error message
  free_array(split);
  return (true);
}
