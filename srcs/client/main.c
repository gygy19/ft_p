/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:04:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/15 20:04:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

t_socket_client	*load_struct_socket_client(void)
{
	t_socket_client	*client;

	if (!(client = malloc(sizeof(t_socket_client))))
		return (NULL);
	client->server = NULL;
	client->host = NULL;
	client->port = 0;
	client->send = send_message;
	client->message = NULL;
	client->cmds = NULL;
	client->serialize = ft_sprintf;
	client->current_cmd = new_command(client);
	return (client);
}

void			loadpwd(t_socket_client *client, char **env)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split_string(env[i], "=");
		if (ft_strcmp(split[0], "PWD") == 0)
			client->pwd = ft_strdup(split[1]);
		free_array(split);
		i++;
	}
}

int				main(int argc, char **argv, char **env)
{
	t_socket_client *client;

	if (argc == 3)
	{
		client = load_struct_socket_client();
		client->events[0].fd = 0;
		client->events[0].read = read_keys;
		client->events[1].fd = 0;
		client->events[1].read = read_keys;
		load_command_pointer(client);
		load_received_messages(client);
		load_termios_console();
		loadpwd(client, env);
		if (gethostbyname(argv[1])\
			&& open_socket_connection(client, argv[1], ft_atoi(argv[2])))
		{
			print_prompt(client);
			client_handler(client);
		}
	}
	return (0);
}
