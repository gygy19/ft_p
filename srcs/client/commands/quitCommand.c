/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 06:59:42 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 06:59:44 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	processquitcommand(t_socket_client *client, char **split)
{
	(void)split;
	(void)client;
	ft_printf("Connection Closed\n");
	exit(0);
	return (true);
}
