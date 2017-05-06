/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getPartUploadProtocolMessage.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 09:55:45 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 09:55:47 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN   processReceivedgetPartUploadProtocolMessage(t_socket_client *client, char *message)
{
  size_t partId;

  if (client->upload == NULL)
    return (false);
  partId = ft_atoi(message);
  (void)partId;
  if (uploadPart(client->upload))
  {
    client->send(client, client->serialize("%c%d", 105, client->upload->partsize));
    ft_printf("SEND partsiz : %d\n", client->upload->partsize);
    send(client->sockfd, client->upload->part, client->upload->partsize, 0);
  }
  return (true);
}
