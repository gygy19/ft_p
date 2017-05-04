/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLoader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:32:01 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 15:32:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void loadMapOfCommands(t_socket_client *client)
{
  int i;

  i = 0;
  client->commandsMap = newstringhashmap(10);
  while (i < ARRAY_CLIENT_COMMANDS_SIZE)
  {
    ft_printf("%s, %d\n", arrayClientCommands[i].name, arrayClientCommands[i].args_Min);
    client->commandsMap->add(client->commandsMap, arrayClientCommands[i].name, &arrayClientCommands[i]);
    i++;
  }
}
