/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 05:08:27 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 05:08:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	disconnect_command(t_socket_client *client, char **split)
{
	(void)split;
	if (client->host == NULL)
	{
		ft_printf("Error you is not connected from the server\n");
		return (false);
	}
	if (client->host != NULL)
	{
		ft_printf("Server disconnection %s:%d\n", client->host, client->port);
		ft_strdel(&client->host);
	}
	close(client->sockfd);
	client->host = NULL;
	client->events[1].fd = 0;
	client->events[1].read = read_keys;
	return (true);
}
