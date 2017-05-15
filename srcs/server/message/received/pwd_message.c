/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwdProtocolMessage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:27:41 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 19:27:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

BOOLEAN	pwd_message(t_socket_server *server,\
	t_client *client, char *message)
{
	(void)server;
	(void)client;
	(void)message;
	client->send(client, client->serialize("%c%s\n", 12, client->pwd));
	return (true);
}
