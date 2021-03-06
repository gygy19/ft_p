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
#include "printf.h"

static BOOLEAN	is_correct_file(char *path)
{
	if (!file_exists(path))
		return (false);
	if (!is_regular(path))
		return (false);
	if (!(get_file_mode(path) & S_IRUSR))
		return (false);
	return (true);
}

t_upload		*loadnewupload(char *filename, char *path)
{
	struct stat	buf;
	t_upload	*upload;
	int			fd;
	void		*ptr;

	if (!is_correct_file(path))
		return (NULL);
	if (!(upload = (t_upload*)malloc(sizeof(t_upload))))
		return (NULL);
	stat(path, &buf);
	upload->size = buf.st_size;
	upload->path = ft_strdup(path);
	upload->filename = ft_strdup(filename);
	upload->currentpart = 0;
	upload->maxpart = getmaxpart(upload);
	upload->offset = 0;
	upload->type = UPLOAD;
	upload->dest = NULL;
	upload->part = NULL;
	fd = open(upload->path, O_RDONLY);
	ptr = mmap(0, upload->size, PROT_READ, MAP_SHARED, fd, 0);
	upload->content = ft_strnew(upload->size);
	ft_memcpy(upload->content, ptr, upload->size);
	munmap(ptr, upload->size);
	return (upload);
}
