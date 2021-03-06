/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   download_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 00:37:41 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 00:37:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static void	print_file_type(t_upload *upload)
{
	if (ft_strcontains(upload->filename, ".png"))
		ft_printf(" [image/png]");
	else if (ft_strcontains(upload->filename, ".jpg")\
		|| ft_strcontains(upload->filename, ".jpeg"))
		ft_printf(" [image/jpeg]");
}

static void	print_informations(t_upload *upload)
{
	char		c;
	size_t		size;

	size = upload->size;
	c = 'o';
	if (size > 1000000000)
	{
		c = 'G';
		size /= 1000000000;
	}
	else if (size > 1000000)
	{
		c = 'M';
		size /= 1000000;
	}
	else if (size > 1000)
	{
		c = 'K';
		size /= 1000;
	}
	ft_printf("Infos: %s %doctet (%d%c)", upload->filename,\
		upload->size, size, c);
}

static void	start_download(t_socket_client *client, char *filename,\
	char *infos)
{
	t_upload	*download;

	download = loadnewdownload(filename, infos);
	if (download != NULL)
	{
		print_informations(download);
		print_file_type(download);
		ft_putstr("\n");
		client->download = download;
		client->send(client, client->serialize("%c%d", 106,\
			client->download->currentpart));
	}
}

BOOLEAN		download_message(t_socket_client *client, char *message)
{
	char		**split;
	char		*infos;
	char		*path;

	split = ft_split_string(message, "|");
	if (array_length(split) != 3)
		return (false);
	if (client->download_directory[\
		ft_strlen(client->download_directory) - 1] == '/')
		path = ft_strjoin(client->download_directory, split[0]);
	else
		path = ft_dstrjoin(ft_strjoin(client->download_directory, "/"),\
			split[0], 1);
	infos = ft_sprintf("%s|%d|%s", split[1], ft_atoi(split[2]), path);
	ft_printf("\033[uft_get: Loading File...\n");
	start_download(client, split[0], infos);
	ft_strdel(&path);
	free_array(split);
	return (true);
}
