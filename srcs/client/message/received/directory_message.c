/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directoryProtocolMessage.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 00:13:34 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 00:13:36 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	directory_message(t_socket_client *client, char *message)
{
	char	**split;
	int		i;

	(void)client;
	split = ft_split_string(message, "|");
	i = 0;
	if (array_length(split) <= 0)
		return (false);
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
	return (true);
}
