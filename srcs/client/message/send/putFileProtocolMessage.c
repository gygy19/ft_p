/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putFileProtocolMessage.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 01:37:54 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 01:37:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"
#include "ftp_upload.h"

char      *getfilename(char *path)
{
  int   i;
  char  *tmp;

  i = ft_strlen(path);
  if (i > 0 && path[i] == '/')
    tmp = ft_strndup(path, i);
  else
    tmp = ft_strdup(path);
  i = ft_strlen(tmp);
  while (i > 0 && tmp[i] != '/')
    i--;
  if (i < 0)
    return (tmp);
  tmp = ft_dstrjoin("", ft_strdup(tmp + i), 2);
  return (tmp);
}

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

BOOLEAN   processSendputFileProtocolMessage(t_socket_client *client, char **split)
{
  t_upload  *upload;
  char      *filename;
  char      *path;

  if (array_length(split) <= 1)
    return (false);
  filename = getfilename(split[1]);
  if (split[1][0] != '/' && split[1][0] != '-' && split[1][0] != '~')
    path = ft_dstrjoin(ft_strjoin(client->pwd, "/"), split[1], 1);
  else
    path = ft_strdup(split[1]);
  ft_printf("Loading File...\n");

  upload = loadnewUpload(filename, path);
  if (upload != NULL)
  {
    printPurcentage(client, upload);
    client->send(client, client->serialize("%c%s|%s|%d", 104, upload->filename, upload->path, upload->size));
    client->upload = upload;
  }
  else
  {
    ft_printf("ft_put: no such file or directory: %s\n", split[1]);
  }
  ft_strdel(&filename);
  ft_strdel(&path);
  return (true);
}
