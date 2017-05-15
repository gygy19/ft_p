/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_aks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:51:45 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:51:47 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int			send_message(t_client *client, char *message)
{
	int		r;
	int		length;

	message = ft_dstrjoin_char(message, '\n', 1);
	length = ft_strlen(message);
	r = send(client->fd, &length, sizeof(int), 0);
	r = send(client->fd, message, length, 0);
	ft_strdel(&message);
	return (!(r < 0));
}

static int	read_new_message(t_client *client)
{
	size_t	ret;
	int		packetlength;

	if (!(ret = recv(client->fd, &packetlength, sizeof(int), 0)))
		return (0);
	if (packetlength <= 0 || packetlength > 100000000)
		return (0);
	client->message = ft_strnew(packetlength);
	ret = recv(client->fd, client->message, packetlength, 0);
	if (ft_strlen(client->message) <= 0)
	{
		ft_strdel(&client->message);
		client->message = NULL;
		return (0);
	}
	return (1);
}

int			received_message(t_socket_server *server, t_client *client)
{
	if (!read_new_message(client))
		return (0);
	if (client->message[ft_strlen(client->message) - 1] != '\n')
		return (1);
	client->message[ft_strlen(client->message) - 1] = '\0';
	ft_printf("{color70}New message from [%s:%d] ({color149}%d%s\n",\
		inet_ntoa(client->in.sin_addr),\
		ntohs(client->in.sin_port),\
		client->message[0],\
		"{reset}{color70}){reset}");
	server->data_processor(server, client, client->message);
	ft_strdel(&client->message);
	client->message = NULL;
	return (1);
}
