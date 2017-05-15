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

t_upload	*loadnewdownload(char *filename, char *infos)
{
	t_upload	*upload;
	char		**split;
	int			fileid;

	fileid = 0;
	split = ft_split_string(infos, "|");
	if (!(upload = (t_upload*)malloc(sizeof(t_upload))))
		return (NULL);
	upload->size = ft_atoi(split[1]);
	upload->path = ft_strdup(split[0]);
	upload->filename = ft_strdup(filename);
	upload->currentpart = 0;
	upload->maxpart = getmaxpart(upload);
	upload->offset = 0;
	upload->type = DOWNLOAD;
	upload->dest = ft_strdup(split[2]);
	while (file_exists(upload->dest))
	{
		ft_strdel(&upload->dest);
		upload->dest = ft_dstrjoin(ft_strdup(split[2]),\
			ft_dstrjoin("(", ft_dstrjoin(ft_itoa(++fileid), ")", 1), 2), 3);
	}
	free_array(split);
	return (upload);
}
