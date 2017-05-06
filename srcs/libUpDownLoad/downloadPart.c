/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   downloadPart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:34:12 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:34:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_upload.h"
#include "libfile.h"

void    downloadPart(t_upload *upload, char *part, size_t size)
{
  int   fd;

  if (!file_exists(upload->dest))
    fd = open(upload->dest, O_CREAT | O_RDWR);
  else
    fd = open(upload->dest, O_APPEND | O_RDWR);
  upload->currentPart++;
  if (upload->currentPart > upload->maxPart)
    return ;
  write(fd, part, size);
  close(fd);
}
