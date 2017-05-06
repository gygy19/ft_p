/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadnewUpload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:33:42 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:33:43 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_upload.h"
#include "libfile.h"

t_upload        *loadnewUpload(char *filename, char *path)
{
  struct stat buf;
  t_upload    *upload;

  if (!file_exists(path))
    return (NULL);
  if (!is_regular(path))
    return (NULL);
  if (!(upload = (t_upload*)malloc(sizeof(t_upload))))
    return (NULL);
  stat(filename, &buf);
  upload->size = buf.st_size;
  upload->path = ft_strdup(path);
  upload->filename = ft_strdup(filename);
  upload->currentPart = 0;
  upload->maxPart = (100 * upload->size) / 1000;
  upload->offset = 0;
  upload->type = UPLOAD;
  upload->dest = NULL;
  return (upload);
}
