/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getFileProtocolMessage.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 01:37:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 01:37:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	processsendgetfileprotocolmessage(t_socket_client *client, char **split)
{
	if (array_length(split) <= 1)
		return (false);
	client->send(client, client->serialize("%c%s", 103, split[1]));
	return (true);
}
