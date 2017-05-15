/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_upload.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:19:33 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:19:34 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_UPLOAD_H
# define FTP_UPLOAD_H

# include <libft.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>

# define UPLOAD 1
# define DOWNLOAD 2

typedef struct	s_upload
{
	char		*filename;
	char		*path;
	char		*content;
	size_t		size;
	size_t		offset;
	size_t		currentpart;
	size_t		maxpart;
	size_t		type;
	char		*dest;
	char		*part;
	size_t		partsize;
}				t_upload;

t_upload		*loadnewupload(char *filename, char *path);
t_upload		*loadnewdownload(char *filename, char *infos);
BOOLEAN			uploadpart(t_upload *upload);
void			downloadpart(t_upload *download, char *part, size_t size);

int				getsize(t_upload *upload);
int				getmaxpart(t_upload *upload);

#endif
