/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getFileProtocolMessage.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:06:54 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:06:56 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"
#include "libfile.h"

static void	start_upload(t_socket_server *server, t_client *client,\
	char *filename, char *path)
{
	t_upload	*upload;

	if (ft_strncmp(server->pwd, path, ft_strlen(server->pwd)))
	{
		client->send(client, client->serialize("%c%s%s\n", INFOS_MESSAGE,\
			"ft_get: path restricted: ", server->pwd));
		return ;
	}
	if ((upload = loadnewupload(filename, path)) != NULL)
	{
		client->send(client, client->serialize("%c%s|%s|%d", 103,\
			upload->filename, upload->path, upload->size));
		client->upload = upload;
	}
	else if (file_exists(path) && !(get_file_mode(path) & S_IRUSR))
		client->send(client, client->serialize("%c%s%s\n", INFOS_MESSAGE,\
			"ft_get: Permission denied: ", filename));
	else
		client->send(client, client->serialize("%c%s%s\n", INFOS_MESSAGE,\
			"ft_get: no such file or directory: ", filename));
}

BOOLEAN		download_file_message(t_socket_server *server,\
	t_client *client, char *message)
{
	char		**split;
	char		*path;

	(void)server;
	split = ft_split_string(message, "|");
	if (array_length(split) == 0)
		return (false);
	if (split[0][0] == '/')
		path = ft_strdup(split[0]);
	else if (client->pwd[ft_strlen(client->pwd) - 1] == '/')
		path = ft_strjoin(client->pwd, split[0]);
	else
		path = ft_dstrjoin(ft_strjoin(client->pwd, "/"), split[0], 1);
	start_upload(server, client, split[0], path);
	ft_strdel(&path);
	free_array(split);
	return (true);
}
