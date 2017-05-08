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
#include "printf.h"

void    downloadPart(t_upload *upload, char *part, size_t size)
{
  int   fd;

  fd = open(upload->dest,\
    O_CREAT | O_APPEND | O_WRONLY | O_NONBLOCK,\
    S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  upload->currentPart++;
  if (upload->currentPart > upload->maxPart)
    return ;
  upload->offset += size;
  write(fd, (void*)part, size);
  close(fd);
}
