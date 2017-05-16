/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconnect_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 04:56:28 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 04:56:29 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	reconnect_command(t_socket_client *client, char **split)
{
	char *oldhost;

	(void)split;
	if (client->host != NULL)
	{
		ft_printf("You is connected on %s\n", client->host);
		return (false);
	}
	if (client->oldhost == NULL)
	{
		ft_printf("Error no oldhost detected\n");
		return (false);
	}
	oldhost = client->oldhost;
	if (!open_socket_connection(client, client->oldhost, client->port))
		return (false);
	ft_strdel(&oldhost);
	return (true);
}
