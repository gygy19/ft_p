/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_message_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 19:46:52 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/20 19:46:53 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"
#include "libfile.h"

char		*get_perm(char *file)
{
	char		x;
	struct stat	stats;
	char		*perms;

	x = '-';
	lstat(file, &stats);
	if (S_ISLNK(stats.st_mode))
		x = 'l';
	else if (S_ISCHR(stats.st_mode))
		x = 'c';
	else if (S_ISDIR(stats.st_mode))
		x = 'd';
	perms = ft_sprintf("%c%c%c%c%c%c%c%c%c%c", x,\
		((stats.st_mode & S_IRUSR) ? 'r' : '-'),\
		((stats.st_mode & S_IWUSR) ? 'w' : '-'),\
		((stats.st_mode & S_IXUSR) ? 'x' : '-'),\
		((stats.st_mode & S_IRGRP) ? 'r' : '-'),\
		((stats.st_mode & S_IWGRP) ? 'w' : '-'),\
		((stats.st_mode & S_IXGRP) ? 'x' : '-'),\
		((stats.st_mode & S_IROTH) ? 'r' : '-'),\
		((stats.st_mode & S_IWOTH) ? 'w' : '-'),\
		((stats.st_mode & S_IXOTH) ? 'x' : '-'));
	return (perms);
}

BOOLEAN		senderror(t_client *client, char *file)
{
	if (file != NULL)
		client->send(client, client->serialize(\
			"%cft_ls: %s: No such file or directory\n",\
			INFOS_MESSAGE, file));
	else
		client->send(client, client->serialize(\
			"%cft_ls: %s: directory is deleted\n",\
			INFOS_MESSAGE, client->pwd));
	return (false);
}

char		**get_flags(char **args, int *flags)
{
	char **tmp;

	if (array_length(args) == 0)
		return (args);
	if (args[0][0] != '-')
		return (args);
	if (ft_strcontains(args[0], "a"))
		*flags += 1024;
	if (ft_strcontains(args[0], "l"))
		*flags += 2048;
	if (array_length(args) == 2)
	{
		tmp = ft_split_string(args[1], " ");
		free_array(args);
		ft_printf("%s\n", tmp[0]);
		return (tmp);
	}
	else
		free_array(args);
	return (ft_split_string("", "."));
}
