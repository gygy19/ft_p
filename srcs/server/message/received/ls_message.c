/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsProtocolMessage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 00:24:04 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 00:24:06 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"
#include "libfile.h"

static DIR		*open_directory(char *dir)
{
	DIR	*dirp;

	dirp = NULL;
	if (is_dir(dir) == false)
		return (NULL);
	dirp = opendir(dir);
	return (dirp);
}

static char		*get_name_form_flags(char *message, char *file,\
	char *filename, int flags)
{
	char			*tmp;

	tmp = message;
	if (flags & 2048)
		message = ft_sprintf("%s%s%s %s", message,\
			(ft_strlen(message) != 0 ? "|" : ""), get_perm(file), filename);
	else
		message = ft_sprintf("%s%s%s", message,\
			(ft_strlen(message) != 0 ? "|" : ""), filename);
	ft_strdel(&tmp);
	ft_strdel(&file);
	ft_strdel(&filename);
	return (message);
}

static char		*parsefiletomessage(char *path, int flags)
{
	char *message;

	if (!file_exists(path))
		return (NULL);
	if (!is_regular(path))
		return (NULL);
	message = ft_strnew(0);
	message = get_name_form_flags(message,\
		ft_strdup(path), ft_strdup(path), flags);
	return (message);
}

static char		*parsedirectorytomessage(char *dir, int flags)
{
	DIR				*dirp;
	struct dirent	*files;
	char			*message;

	if (!is_dir(dir))
		return (parsefiletomessage(dir, flags));
	if ((dirp = open_directory(dir)) == NULL)
		return (NULL);
	files = malloc(sizeof(struct dirent));
	message = ft_strnew(0);
	while ((files = readdir(dirp)) != 0)
	{
		if (files->d_name[0] == '.' && !(flags & 1024))
			continue ;
		message = get_name_form_flags(message,\
			ft_strjoin(dir[ft_strlen(dir) - 1] != '/' ?\
			ft_strjoin(dir, "/") : dir, files->d_name),\
			ft_strdup(files->d_name), flags);
	}
	closedir(dirp);
	free(files);
	return (message);
}

BOOLEAN			ls_message(t_socket_server *server,\
	t_client *client, char *message)
{
	char	*directoryfiles;
	char	**split;
	int		flags;

	flags = 0;
	split = ft_split_string(message, "|");
	split = get_flags(split, &flags);
	if (client->pwd == NULL && array_length(split) == 0)
		return (false);
	if (array_length(split) == 0)
		directoryfiles = parsedirectorytomessage(client->pwd, flags);
	else
		directoryfiles = parsedirectorytomessage(split[0], flags);
	if (directoryfiles == NULL)
		return (senderror(client, split[0]));
	if (ft_strlen(directoryfiles) == 0)
		return (true);
	(void)server;
	client->send(client, client->serialize("%c%s",\
		DIRECTORY_CONTENT_MESSAGE, directoryfiles));
	free_array(split);
	return (true);
}
