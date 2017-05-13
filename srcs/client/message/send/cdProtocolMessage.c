/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdProtocolMessage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:46:21 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 17:46:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	processsendcdprotocolmessage(t_socket_client *client, char **split)
{
	if (array_length(split) <= 1)
		return (false);
	client->send(client, client->serialize("%c%s", 100, split[1]));
	return (true);
}
