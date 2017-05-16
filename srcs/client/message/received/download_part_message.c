/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getPartDownloadProtocolMessage.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:23:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/09 17:23:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static char	*read_on_socket_file_content(t_socket_client *client, size_t size)
{
	char	*part;
	char	buffer[4096 + 1];
	size_t	currentret;
	size_t	ret;

	currentret = 0;
	ret = 0;
	part = ft_strnew(size + 1);
	while (currentret < size)
	{
		ret = recv(client->sockfd, buffer,\
			(size - currentret) < 4096 ? (size - currentret) : 4096, 0);
		buffer[ret] = '\0';
		ft_memcpy(part + currentret, buffer, ret);
		currentret += ret;
	}
	return (part);
}

static void	print_purcentage(t_socket_client *client, t_upload *upload)
{
	char	*rg;
	int		pur;
	int		i;

	if (upload->currentpart <= 1)
		ft_putstr("\n\n\n");
	ft_putstr("\033[u");
	ft_putstr("\033[s\033[3A");
	ft_printf("-----------------------------------------\n");
	pur = (30 * upload->offset) / upload->size;
	rg = ft_strnew(pur + 1);
	i = 0;
	while (i < pur)
	{
		rg[i] = '=';
		i++;
	}
	rg[i] = '>';
	ft_printf("%-3d%%[%-30s]%s\n", (100 * upload->offset) / upload->size,\
		rg, "1Mo/s");
	ft_printf("-----------------------------------------\n");
	if (upload->currentpart == upload->maxpart)
		ft_printf("\033[Kft_get: Upload finished\n");
	reprint_line(client, upload->currentpart == upload->maxpart);
}

BOOLEAN		download_part_message(t_socket_client *client, char *message)
{
	char	**split;
	size_t	size;
	char	*part;
	int		savepourcentage;

	split = ft_split_string(message, "|");
	if (array_length(split) != 1)
		return (false);
	if (client->download == NULL)
		return (false);
	size = ft_atoi(split[0]);
	part = read_on_socket_file_content(client, size);
	savepourcentage = (100 * client->download->offset) / client->download->size;
	downloadpart(client->download, part, size);
	if (savepourcentage < (int)((100 * client->download->offset) / client->download->size)
		|| client->download->currentpart == 1)
		print_purcentage(client, client->download);
	if (client->download->currentpart < client->download->maxpart)
		client->send(client, client->serialize("%c%d", 106,\
			client->download->currentpart));
	free_array(split);
	return (true);
}
