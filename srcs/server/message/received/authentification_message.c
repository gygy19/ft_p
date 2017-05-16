/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentification_message.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 07:32:30 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 07:32:32 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

BOOLEAN	authentification_message(t_socket_server *server, t_client *client,\
	char *message)
{
	(void)server;
	(void)message;
	client->authentified = true;
	return (true);
}
