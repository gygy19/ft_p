/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putFileProtocolMessage.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 01:37:54 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 01:37:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN   processSendputFileProtocolMessage(t_socket_client *client, char **split)
{
  if (array_length(split) <= 1)
    return (false);
  client->send(client, client->serialize("%c%s", 104, split[1]));
  return (true);
}
