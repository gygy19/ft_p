/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_switcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:18:00 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:18:01 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void			switch_command(t_socket_client *client, char *cmd)
{
	char				**split;
	t_CommandHooker		*command;

	split = ft_split_string(cmd, " ");
	if (array_length(split) == 0)
		return ;
	command = (t_CommandHooker*)client->commandsMap->get(client->commandsMap,\
		split[0]);
	if (command != NULL && (array_length(split) - 1) >= command->args_Min)
		command->execute(client, split);
	free_array(split);
}
