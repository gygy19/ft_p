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

static void printFileType(t_upload *upload)
{
  if (ft_strcontains(upload->filename, ".png"))
    ft_printf(" [image/png]");
  else if (ft_strcontains(upload->filename, ".jpg")
    || ft_strcontains(upload->filename, ".jpeg"))
    ft_printf(" [image/jpeg]");
}

static void printInformations(t_upload *upload)
{
  char    c;
  size_t  size;

  size = upload->size;
  c = 'o';
  if (size > 1000000000)
  {
    c = 'G';
    size /= 1000000000;
  }
  else if (size > 1000000)
  {
    c = 'M';
    size /= 1000000;
  }
  else if (size > 1000)
  {
    c = 'K';
    size /= 1000;
  }
  ft_printf("Length: %d (%d%c)", upload->size, size, c);
}

static void printPurcentage(t_socket_client *client, t_upload *upload)
{
  ft_putstr("\033[u\033[K");
  printInformations(upload);
  printFileType(upload);
  ft_printf("\n\n");
  ft_printf("(%d%%/100%%)\n", (100 * upload->offset) / upload->size);
  ft_putstr("\033[s");
  reprint_line(client);
}

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
    send(client->sockfd, client->upload->part, client->upload->partsize, 0);
  }
  printPurcentage(client, client->upload);
  return (true);
}
