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

static char		*parsedirectorytomessage(char *dir, int flags)
{
	DIR				*dirp;
	struct dirent	*files;
	char			*message;
	char			*tmp;

	if (!is_dir(dir))
		return (NULL);
	if ((dirp = open_directory(dir)) == NULL)
		return (NULL);
	files = malloc(sizeof(struct dirent));
	message = ft_strnew(0);
	while ((files = readdir(dirp)) != 0)
	{
		if (files->d_name[0] == '.' && flags & 1024)
			continue ;
		tmp = message;
		message = ft_sprintf("%s%s%s", message,
		(ft_strlen(message) != 0 ? "|" : ""),
		files->d_name);
		ft_strdel(&tmp);
	}
	closedir(dirp);
	free(files);
	return (message);
}

static BOOLEAN	senderror(t_client *client, char *file)
{
	if (file != NULL)
		client->send(client, client->serialize(\
			"%cft_ls: %s: No such file or directory\n",\
			INFOS_MESSAGE, file));
	else
		client->send(client, client->serialize(\
			"%cft_ls: %s: directory is deleted\n",\
			INFOS_MESSAGE, client->pwd));
	return (false);
}

BOOLEAN			ls_message(t_socket_server *server,\
	t_client *client, char *message)
{
	char	*directoryfiles;
	char	**split;

	split = ft_split_string(message, "|");
	if (client->pwd == NULL && array_length(split) == 0)
		return (false);
	if (array_length(split) == 0)
		directoryfiles = parsedirectorytomessage(client->pwd, 1024);
	else
		directoryfiles = parsedirectorytomessage(split[0], 1024);
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
