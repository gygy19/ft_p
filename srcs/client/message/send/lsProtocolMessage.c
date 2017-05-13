/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsProtocolMessage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 00:47:30 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 00:47:32 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	processsendlsprotocolmessage(t_socket_client *client, char **split)
{
	if (array_length(split) == 1)
		client->send(client, client->serialize("%c", 102));
	else
		client->send(client, client->serialize("%c%s", 102, split[1]));
	return (true);
}
