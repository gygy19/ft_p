/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 07:58:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/17 07:58:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int			data_processor(t_socket_server *server, t_client *client,\
	char *message)
{
	char	*finalmessage;
	char	action;
	char	type;

	action = '\0';
	type = '\0';
	if (ft_strlen(message) > 0)
		action = message[0];
	if (ft_strlen(message) > 1)
		type = message[1];
	finalmessage = ft_strsub(message, 2, ft_strlen(message));

	(void)action;
	(void)type;
	(void)server;
	(void)client;
	
	if (finalmessage != NULL)
		ft_strdel(&finalmessage);
	return (0);
}
