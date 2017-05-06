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
#include "xor.h"

int			send_message(t_client *client, char *message)
{
	int		r;
	char	*crypted;

	message = ft_dstrjoin_char(message, '\n', 1);
	crypted = crypt_string_to_xor(message);
	message[ft_strlen(message) - 1] = '\0';
	r = send(client->fd, crypted, ft_strlen(crypted), 0);
	ft_strdel(&message);
	ft_strdel(&crypted);
	return (!(r < 0));
}

static int	read_new_message(t_client *client)
{
	size_t	ret;
	char	buffer[1 + 1];

	ret = recv(client->fd, buffer, 1, 0);
	buffer[ret] = '\0';
	if (client->message == NULL)
		client->message = ft_strdup(buffer);
	else
		client->message = ft_dstrjoin(client->message, buffer, 1);
	return (buffer[0] != '\0');
}

int			received_message(t_socket_server *server, t_client *client)
{
	char	*uncrypted;

	if (!read_new_message(client))
		return (0);
	uncrypted = uncrypt_xor_to_string(client->message);
	if (uncrypted[ft_strlen(uncrypted) - 1] != '\n')
		return (1);
	uncrypted[ft_strlen(uncrypted) - 1] = '\0';
	ft_printf("{color70}New message from [%s:%d] ({color149}%d{reset}{color70}){reset}\n",\
		inet_ntoa(client->in.sin_addr),\
		ntohs(client->in.sin_port),\
		uncrypted[0]);
	server->data_processor(server, client, uncrypted);
	ft_strdel(&uncrypted);
	ft_strdel(&client->message);
	client->message = NULL;
	return (1);
}
