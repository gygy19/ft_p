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

BOOLEAN uploadpart(t_upload *upload)
{
  int   len;

  if (!file_exists(upload->path))
    return (false);
  len = getsize(upload);
  upload->currentPart++;
  if (upload->currentPart > upload->maxPart)
    return (false);
  if (upload->currentPart == upload->maxPart)
    len = upload->size - upload->offset;
  if (len <= 0)
  {
    upload->part = ft_strdup("");
    upload->partsize = 0;
    return (true);
  }
  upload->part = ft_strnew(len);
  ft_memcpy(upload->part, upload->content + upload->offset, len);
  upload->offset += len;
  upload->partsize = len;
  return (true);
}
