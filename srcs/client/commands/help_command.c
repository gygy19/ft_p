/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 04:48:57 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 04:48:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

BOOLEAN	help_command(t_socket_client *client, char **split)
{
	(void)split;
	(void)client;
	ft_printf("--------------------------------------------------------\n");
	ft_printf("List of commands :\n");
	ft_printf("help\n");
	ft_printf("pwd                          (print current path)\n");
	ft_printf("cd <directory>               (move to directory)\n");
	ft_printf("ls <directory>               (print directory content)\n");
	ft_printf("get <file>                   (download file)\n");
	ft_printf("put <file>                   (upload file)\n");
	ft_printf("quit or exit                 (exit this program)\n");
	ft_printf("disconnect                   (disconnect of the server)\n");
	ft_printf("reconnect                    (reconnect from the server)\n");
	ft_printf("connect <host> <port>        (exit this program)\n");
	ft_printf("setdownloadpath <directory>  (change download directory)\n");
	ft_printf("getdownloadpath              (print download directory)\n");
	ft_printf("--------------------------------------------------------\n");
	return (true);
}
