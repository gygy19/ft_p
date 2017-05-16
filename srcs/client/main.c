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
#include "libfile.h"

t_socket_client	*load_struct_socket_client(void)
{
	t_socket_client	*client;

	if (!(client = malloc(sizeof(t_socket_client))))
		return (NULL);
	client->server = NULL;
	client->host = NULL;
	client->oldhost = NULL;
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
	client->pwd = NULL;
	while (env[i])
	{
		split = ft_split_string(env[i], "=");
		if (ft_strcmp(split[0], "PWD") == 0)
			client->pwd = ft_strdup(split[1]);
		free_array(split);
		i++;
	}
	if (client->pwd == NULL)
	{
		ft_printf("PWD environement doesn't exit please add PWD\n");
		exit(0);
	}
	if (!file_exists(client->pwd) || !is_dir(client->pwd))
	{
		ft_printf("PWD environement doesn't exit or is %s\n",\
			"not a directory please change PWD");
		exit(0);
	}
	client->download_directory = ft_strdup(client->pwd);
}

static char		*parse_host(char **argv)
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

static int		parse_port(char **argv, int argc)
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

int				main(int argc, char **argv, char **env)
{
	t_socket_client *client;
	char			*host;

	if (argc == 2 || argc == 3)
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
		host = parse_host(argv);
		if (gethostbyname(host)\
			&& open_socket_connection(client, host, parse_port(argv, argc)))
		{
			print_prompt(client);
			client_handler(client);
		}
	}
	return (0);
}
