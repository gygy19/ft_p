/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdProtocolMessage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:05:54 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 18:05:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

BOOLEAN   processReceivedcdProtocolMessage(t_socket_server *server, t_client *client, char *message)
{
  (void)server;
  (void)client;
  (void)message;
  return (true);
}
