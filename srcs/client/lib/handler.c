/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 08:14:06 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 08:14:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"
#include "xor.h"

int			client_handler(t_socket_client *client)
{
	fd_set	rdfs;
	int		i;

	while (1)
	{
		i = 0;
		FD_ZERO(&rdfs);
		while (i < 2)
		{
			FD_SET(client->events[i].fd, &rdfs);
			i++;
		}
		if (select(client->events[1].fd + 1, &rdfs, NULL, NULL, NULL) == -1)
			return (1);
		i = 0;
		while (i < 2)
		{
			if (FD_ISSET(client->events[i].fd, &rdfs))
				client->events[i].read(client);
			i++;
		}
	}
	return (0);
}

int			send_message(t_socket_client *client, char *message)
{
	int		r;
	char	*crypted;
	int		length;

	if (message == NULL || ft_strlen(message) <= 0)
		return (0);
	message = ft_dstrjoin_char(message, '\n', 1);
	crypted = crypt_string_to_xor(message);
	length = ft_strlen(crypted);
	r = send(client->sockfd, &length, sizeof(int), 0);
	r = send(client->sockfd, crypted, length, 0);
	ft_strdel(&message);
	ft_strdel(&crypted);
	return (!(r < 0));
}

void		server_disconnect(t_socket_client *client)
{
	if (client->host != NULL)
	{
		ft_printf("Server disconnection %s:%d\n", client->host, client->port);
		ft_strdel(&client->host);
	}
	else
		ft_printf("Server disconnection\n");
	client->host = NULL;
	client->events[1].fd = 0;
	client->events[1].read = read_keys;
	reprint_line(client, true);
}

static void	read_message(t_socket_client *client, int packetlength)
{
	size_t	ret;

	client->message = ft_strnew(packetlength);
	ret = recv(client->sockfd, client->message, packetlength, 0);
	if (ft_strlen(client->message) == 0)
	{
		server_disconnect(client);
		ft_strdel(&client->message);
		client->message = NULL;
		return ;
	}
}

static void	read_new_message(t_socket_client *client)
{
	size_t	ret;
	int		packetlength;

	if (!(ret = recv(client->sockfd, &packetlength, sizeof(int), 0)))
	{
		server_disconnect(client);
		ft_strdel(&client->message);
		client->message = NULL;
		return ;
	}
	read_message(client, packetlength);
}

void		received_message(t_socket_client *client)
{
	char	*uncrypted;
	char	*message;

	read_new_message(client);
	if (client->message == NULL)
		return ;
	uncrypted = uncrypt_xor_to_string(client->message);
	if (uncrypted[ft_strlen(uncrypted) - 1] != '\n')
		return ;
	message = ft_strndup(uncrypted, ft_strlen(uncrypted) - 1);
	data_processor(client, message);
	ft_strdel(&message);
	ft_strdel(&uncrypted);
	ft_strdel(&client->message);
	client->message = NULL;
}
