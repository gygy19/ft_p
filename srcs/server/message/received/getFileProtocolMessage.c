/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getFileProtocolMessage.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:06:54 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:06:56 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

BOOLEAN   processReceivedgetFileProtocolMessage(t_socket_server *server,\
  t_client *client, char *message)
{
  (void)server;
  char  **split;
  char  *file;

  split = ft_split_string(message, "|");
  if (array_length(split) == 0)
    return (false);
  if (client->pwd[ft_strlen(client->pwd) - 1] == '/')
    file = ft_strjoin(client->pwd, split[0]);
  else
    file = ft_dstrjoin(ft_strjoin(client->pwd, "/"), split[0], 1);
  free_array(split);
  return (true);
}
