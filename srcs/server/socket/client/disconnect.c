/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_disconnect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:11:57 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:12:00 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static void	print_disconnect_message(t_client *client)
{
	ft_printf("Client (%d) disconnect\n", client->fd);
}

t_client	*socket_disconnect(t_socket_server *server, t_client *client)
{
	t_client *left;
	t_client *right;

	left = client->left;
	right = client->right;
	print_disconnect_message(client);
	if (left && right)
	{
		right->left = left;
		left->right = right;
	}
	if (left && !right)
		left->right = NULL;
	if (!left && right)
	{
		right->left = NULL;
		server->clients = right;
	}
	close(client->fd);
	client->fd = 0;
	if (client->right == NULL && client->left == NULL)
		server->clients = NULL;
	if (right)
		return (right);
	return (NULL);
}
