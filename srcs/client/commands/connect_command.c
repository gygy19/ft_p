/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 05:08:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 05:08:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static char	*parse_host(char **argv)
{
	char			**split;
	char			*host;

	split = ft_split_string(argv[1], ":");
	if (array_length(split) == 0)
	{
		free_array(split);
		return (ft_strdup(""));
	}
	host = ft_strdup(split[0]);
	free_array(split);
	return (host);
}

static int	parse_port(char **argv, int argc)
{
	char			**split;

	split = ft_split_string(argv[1], ":");
	if (array_length(split) == 2)
	{
		free_array(split);
		return (ft_atoi(split[1]));
	}
	if (argc != 3)
	{
		free_array(split);
		return (0);
	}
	free_array(split);
	return (ft_atoi(argv[2]));
}

BOOLEAN		connect_command(t_socket_client *client, char **split)
{
	char	*host;
	int		port;

	if (client->host != NULL)
	{
		ft_printf("Please disconnect from the server\n");
		return (false);
	}
	if (array_length(split) != 2 && array_length(split) != 3)
	{
		ft_printf("connect <host> <port>\n");
		return (false);
	}
	host = parse_host(split);
	port = parse_port(split, array_length(split));
	if (!gethostbyname(host))
	{
		ft_printf("Error format host ip\n");
		return (false);
	}
	if (open_socket_connection(client, host, port))
		return (true);
	return (false);
}
