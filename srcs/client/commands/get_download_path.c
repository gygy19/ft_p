/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_download_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 07:09:01 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 07:09:03 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	get_download_path_command(t_socket_client *client, char **split)
{
	(void)split;
	if (client->download_directory == NULL)
	{
		ft_printf("Error downloadpath is null\n");
		return (false);
	}
	ft_printf("Download path directory is :\n%s\n", client->download_directory);
	return (true);
}
