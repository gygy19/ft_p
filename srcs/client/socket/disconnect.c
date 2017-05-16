/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 04:45:45 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 04:45:46 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

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
