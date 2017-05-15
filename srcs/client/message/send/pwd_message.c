/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwdProtocolMessage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:32:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 19:32:44 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	pwd_message(t_socket_client *client, char **split)
{
	(void)split;
	client->send(client, client->serialize("%c", 101));
	return (true);
}
