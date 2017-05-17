/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsProtocolMessage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 00:24:04 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 00:24:06 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"
#include "libfile.h"

static DIR		*open_directory(char *dir)
{
	DIR	*dirp;

	dirp = NULL;
	if (is_dir(dir) == false)
		return (NULL);
	dirp = opendir(dir);
	return (dirp);
}

static char	*get_perm(char *file)
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

static char	*get_name_form_flags(char *message, char *file, char *filename, int flags)
{
	char			*tmp;

	tmp = message;
	if (flags & 2048)
		message = ft_sprintf("%s%s%s %s", message, (ft_strlen(message) != 0 ? "|" : ""), get_perm(file), filename);
	else
		message = ft_sprintf("%s%s%s", message, (ft_strlen(message) != 0 ? "|" : ""), filename);
	ft_strdel(&tmp);
	ft_strdel(&file);
	ft_strdel(&filename);
	return (message);
}

static char		*parsedirectorytomessage(char *dir, int flags)
{
	DIR				*dirp;
	struct dirent	*files;
	char			*message;

	if (!is_dir(dir))
		return (NULL);
	if ((dirp = open_directory(dir)) == NULL)
		return (NULL);
	files = malloc(sizeof(struct dirent));
	message = ft_strnew(0);
	while ((files = readdir(dirp)) != 0)
	{
		if (files->d_name[0] == '.' && !(flags & 1024))
			continue ;
		message = get_name_form_flags(message,\
			ft_strjoin(dir[ft_strlen(dir) - 1] != '/' ?\
			ft_strjoin(dir, "/") : dir, files->d_name),\
			ft_strdup(files->d_name), flags);
	}
	closedir(dirp);
	free(files);
	return (message);
}

static BOOLEAN	senderror(t_client *client, char *file)
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

static char		**get_flags(char **args, int *flags)
{
	if (array_length(args) == 0)
		return (args);
	if (args[0][0] != '-')
		return (args);
	if (ft_strcontains(args[0], "a"))
		*flags += 1024;
	if (ft_strcontains(args[0], "l"))
		*flags += 2048;
	free_array(args);
	return (ft_split_string("", "."));
}

BOOLEAN			ls_message(t_socket_server *server,\
	t_client *client, char *message)
{
	char	*directoryfiles;
	char	**split;
	int		flags;

	flags = 0;
	split = ft_split_string(message, "|");
	split = get_flags(split, &flags);
	if (client->pwd == NULL && array_length(split) == 0)
		return (false);
	if (array_length(split) == 0)
		directoryfiles = parsedirectorytomessage(client->pwd, flags);
	else
		directoryfiles = parsedirectorytomessage(split[0], flags);
	if (directoryfiles == NULL)
		return (senderror(client, split[0]));
	if (ft_strlen(directoryfiles) == 0)
		return (true);
	(void)server;
	client->send(client, client->serialize("%c%s",\
		DIRECTORY_CONTENT_MESSAGE, directoryfiles));
	free_array(split);
	return (true);
}
