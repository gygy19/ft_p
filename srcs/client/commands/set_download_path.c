/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_download_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 06:47:43 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 06:47:44 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"
#include "libfile.h"

static char	*parse_path(char *filename)
{
	char	*path;

	if (filename[0] == '/')
		path = ft_strdup(filename);
	else if (client->pwd[ft_strlen(client->pwd) - 1] == '/')
		path = ft_strjoin(client->pwd, filename);
	else
		path = ft_dstrjoin(ft_strjoin(client->pwd, "/"), filename, 1);
	return (path);
}

BOOLEAN		set_download_path_command(t_socket_client *client, char **split)
{
	char	*path;

	if (array_length(split) != 2)
	{
		ft_printf("Error setdownloadpath <directory>\n");
		return (false);
	}
	path = parse_path(split[1]);
	if (!file_exists(path))
	{
		ft_printf("setdownloadpath: %s doens't exist\n", split[1]);
		return (false);
	}
	if (!is_dir(path))
	{
		ft_printf("setdownloadpath: %s is not a directory\n", split[1]);
		return (false);
	}
	ft_strdel(&client->download_directory);
	client->download_directory = path;
	ft_printf("setdownloadpath: new download repository is %s\n", path);
	return (true);
}
