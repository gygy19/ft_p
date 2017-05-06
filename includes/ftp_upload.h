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

typedef struct  s_upload
{
  char          *filename;
  char          *path;
  size_t        size;
  size_t        offset;
  size_t        currentPart;
  size_t        maxPart;
  size_t        type;
  char          *dest;
}               t_upload;

t_upload        *loadnewUpload(char *filename, char *path);
t_upload        *loadnewDownload(char *filename, char *infos);
char            *uploadPart(t_upload *upload);
void            downloadPart(t_upload *download, char *part, size_t size);

#endif
