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
#include "libfile.h"

char		*del_path(char *args, int nbr)
{
	int		i;
	char	*del;

	i = ft_strlen(args);
	if (args[i] == '/' && i == 1)
		return (args);
	i--;
	while (i > 0 && args[i] != '/')
		i--;
	del = ft_strndup(args, i);
	if (del[0] == '\0')
		del = ft_strdup("/");
	ft_strdel(&args);
	if (nbr > 0)
		return (del_path(del, nbr - 1));
	return (del);
}

static char	*getFormatedpwd(char *newPwd, t_client *client, int i, char *pwd)
{
	while (newPwd[i])
	{
		if (newPwd[i] == '.' && newPwd[i + 1] != '\0'\
			&& newPwd[i + 1] == '.' && newPwd[i + 2] != '\0'\
			&& newPwd[i + 2] == '.' && (i += 2))
			pwd = del_path(pwd, 2);
		else if (newPwd[i] == '.' && newPwd[i + 1] != '\0'\
			&& newPwd[i + 1] == '.' && (i += 1))
			pwd = del_path(pwd, 1);
		else if (newPwd[i] == '~' && i == 0)
			pwd = ft_dstrjoin(pwd, client->home, 1);
		else if (newPwd[i] == '-' && i == 0)
			pwd = ft_dstrjoin(pwd, client->oldpwd, 1);
		else if (ft_strlen(pwd) == 0 && newPwd[i] == '/')
			pwd = ft_dstrjoin(pwd, "/", 1);
		else if (ft_strlen(pwd) != 0 &&\
			pwd[ft_strlen(pwd) - 1] != '/' && newPwd[i] == '/')
			pwd = ft_dstrjoin(pwd, "/", 1);
		else if (newPwd[i] != '/')
			pwd = ft_dstrjoin_char(pwd, newPwd[i], 1);
		i++;
	}
	return (pwd);
}

static BOOLEAN ft_cd(t_client *client, char *newPwd)
{
	char *pwd;

	if (newPwd[0] != '/' && newPwd[0] != '~' && newPwd[0] != '-')
		newPwd = ft_dstrjoin(ft_strjoin(client->pwd, "/"), newPwd, 3);
	pwd = getFormatedpwd(newPwd, client, 0, ft_strnew(1));
	if (!is_dir(pwd))
	{
		ft_strdel(&newPwd);
		ft_strdel(&pwd);
		return (false);
	}
	ft_strdel(&client->oldpwd);
	ft_strdel(&newPwd);
	client->oldpwd = client->pwd;
	client->pwd = pwd;
	return (true);
}

BOOLEAN   processReceivedcdProtocolMessage(t_socket_server *server,\
	t_client *client, char *message)
{
	(void)server;
	char  **split;

	split = ft_split_string(message, "|");
	if (client->pwd == NULL && array_length(split) == 0)
		return (false);
	if (!ft_cd(client, ft_strdup(split[0])))
	{
		client->send(client, client->serialize(\
			"%cft_cd: no such file or directory: %s\n", 12, split[0]));
		return (false);
	}
	else
	{
		client->send(client, client->serialize("%cft_cd: Succes %s\n", 12,\
			client->pwd));
	}
	free_array(split);
	return (true);
}
