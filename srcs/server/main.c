/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:04:42 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/15 20:04:43 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"
#include "sig.h"

t_socket_server	*singleton_socket_server(int port)
{
	static t_socket_server *server = NULL;

	if (server == NULL)
	{
		if (!(server = malloc(sizeof(t_socket_server))))
			return (NULL);
		server->port = port;
		server->data_processor = data_processor;
		server->socket_accept = socket_accept;
		server->socket_disconnect = socket_disconnect;
		server->clients = NULL;
	}
	return (server);
}

void			loadpwd(t_socket_server *server, char **env)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split_string(env[i], "=");
		if (ft_strcmp(split[0], "PWD") == 0)
			server->pwd = ft_strdup(split[1]);
		free_array(split);
		i++;
	}
}

int				main(int argc, char **argv, char **env)
{
	int				port;
	t_socket_server	*server;

	if (argc != 2)
		return (1);
	port = ft_atoi(argv[1]);
	if (port <= 0 || port >= 65535)
		return (1);
	if (!(server = singleton_socket_server(port)))
		return (1);
	loadpwd(server, env);
	g_sig = 0;
	signal(SIGINT, ctrlc);
	signal(SIGTSTP, ctrlz);
	signal(SIGQUIT, ctrlq);
	load_received_messages(server);
	return (socket_initialize(server));
}
