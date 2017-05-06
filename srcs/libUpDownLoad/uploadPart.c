/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploadPart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:34:03 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:34:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_upload.h"
#include "libfile.h"

BOOLEAN uploadPart(t_upload *upload)
{
  int   fd;
  void  *ptr;
  int   len;

  if (!file_exists(upload->path))
    return (false);
  len = 1000;
  upload->currentPart++;
  if (upload->currentPart > upload->maxPart)
    return (false);
  if (upload->size < 1000 && upload->currentPart == upload->maxPart)
    len = upload->size;
  else if (upload->currentPart == upload->maxPart)
  {
    len = upload->size - (1000 * upload->maxPart);
  }
  if (len <= 0)
  {
    upload->part = ft_strdup("");
    upload->partsize = 0;
    return (true);
  }
  fd = open(upload->path, O_RDONLY);
  ptr = mmap(0, len, PROT_READ, MAP_SHARED, fd, upload->offset);
  upload->part = ft_strndup((char*)ptr, len);
  munmap(ptr, upload->maxPart);
  upload->partsize = len;
  return (true);
}
