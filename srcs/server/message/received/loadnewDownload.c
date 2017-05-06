/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadnewDownload.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:33:51 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:33:52 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_upload.h"
#include "libfile.h"

t_upload        *loadnewDownload(char *filename, char *infos)//infos == 'path|size|dest'
{
  t_upload    *upload;
  char        **split;

  split = ft_split_string(infos, "|");
  if (!(upload = (t_upload*)malloc(sizeof(t_upload))))
    return (NULL);
  upload->size = ft_atoi(split[1]);
  upload->path = ft_strdup(split[0]);
  upload->filename = ft_strdup(filename);
  upload->currentPart = 0;
  upload->maxPart = (100 * upload->size) / 1000;
  upload->offset = 0;
  upload->type = DOWNLOAD;
  upload->dest = ft_strdup(split[2]);
  free_array(split);
  return (upload);
}
