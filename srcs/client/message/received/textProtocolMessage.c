/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textProtocolMessage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 20:00:49 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 20:00:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	processreceivedtextprotocolmessage(t_socket_client *client,\
	char *message)
{
	(void)client;
	ft_printf("%s", message);
	return (true);
}
