/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getPartUploadProtocolMessage.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 09:55:45 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 09:55:47 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static void	print_purcentage(t_socket_client *client, t_upload *upload)
{
	char	*rg;
	int		pur;
	int		i;

	(void)client;
	if (upload->currentpart == 1)
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
		ft_printf("\033[Kft_put: Upload finished\n");
	reprint_line(client, upload->currentpart == upload->maxpart);
}

BOOLEAN		upload_part_message(t_socket_client *client,\
	char *message)
{
	size_t	partid;
	int		savepourcentage;

	if (client->upload == NULL)
		return (false);
	partid = ft_atoi(message);
	savepourcentage = (100 * client->upload->offset) / client->upload->size;
	if (uploadpart(client->upload))
	{
		client->send(client, client->serialize("%c%d", 105,\
			client->upload->partsize));
		send(client->sockfd, client->upload->part,\
			client->upload->partsize, 0);
		if (savepourcentage <
			(int)((100 * client->upload->offset) / client->upload->size)
			|| client->upload->currentpart == 1)
			print_purcentage(client, client->upload);
	}
	return (true);
}
