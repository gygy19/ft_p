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
  upload = loadnewUpload(filename, path);
  if (upload != NULL)
  {
    ft_printf("Upload -> %s, part[%d/%d](%doctet) path(\"%s\")\n", upload->filename, upload->currentPart, upload->maxPart, upload->size, upload->path);
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
