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

static void printPurcentage(t_socket_client *client, t_upload *upload)
{
  char  *rg;
  int   pur;
  int   i;

  (void)client;
  ft_putstr("\033[u");
  ft_putstr("\033[K");
  ft_putstr("\033[s");
  pur = (30 * upload->offset) / upload->size;
  rg = ft_strnew(pur);
  i = 0;
  while (i < pur)
  {
    rg[i] = '=';
    if (i == 30)
      rg[i] = '>';
    i++;
  }
  ft_printf("%-3d%%[%-30s]\n", (100 * upload->offset) / upload->size, rg);
}

BOOLEAN   processReceivedgetPartUploadProtocolMessage(t_socket_client *client, char *message)
{
  size_t  partId;
  int     savePourcentage;

  if (client->upload == NULL)
    return (false);
  partId = ft_atoi(message);
  (void)partId;
  savePourcentage = (100 * client->upload->offset) / client->upload->size;
  if (uploadPart(client->upload))
  {
    client->send(client, client->serialize("%c%d", 105, client->upload->partsize));
    send(client->sockfd, client->upload->part, client->upload->partsize, 0);
    if (savePourcentage < (int)((100 * client->upload->offset) / client->upload->size))
      printPurcentage(client, client->upload);
  }
  reprint_line(client);

  return (true);
}
