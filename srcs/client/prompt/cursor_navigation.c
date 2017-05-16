/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_navigation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:15:24 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/29 05:15:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static void		move_cursor_right(t_socket_client *client)
{
	if (client->current_cmd->cursor_pos ==\
		ft_strlen(client->current_cmd->cmd))
		return ;
	client->current_cmd->cursor_pos++;
	ft_putstr("\033[1C");
}

static void		move_cursor_left(t_socket_client *client)
{
	if (client->current_cmd->cursor_pos == 0)
		return ;
	client->current_cmd->cursor_pos--;
	ft_putstr("\033[1D");
}

static void		tab_autocomplet(t_socket_client *client)
{
	int	i;

	i = 0;
	if (client->current_cmd->cmd == NULL)
		return ;
	while (i < AR_CMD_SIZE)
	{
		if (!ft_strncmp(client->current_cmd->cmd,\
			g_arrayprotocolmessagessend[i].name,\
			ft_strlen(client->current_cmd->cmd)))
		{
			ft_strdel(&client->current_cmd->cmd);
			client->current_cmd->cmd = \
			ft_strdup(g_arrayprotocolmessagessend[i].name);
			while (client->current_cmd->cursor_pos <\
				ft_strlen(client->current_cmd->cmd))
				move_cursor_right(client);
			ft_printf("\033[u\033[K");
			reprint_line(client, true);
			break ;
		}
		i++;
	}
}

void			move_cursor_to_keycode_dir(t_socket_client *client,\
	int key, char *keys)
{
	if (key == 183 && ft_strlen(keys) == 3 && client->current_cmd->left)
		up_to_next_olded_command(client);
	if (key == 184 && ft_strlen(keys) == 3 && client->current_cmd->right)
		down_to_olded_next_command(client);
	if (key == 185 && ft_strlen(keys) == 3)
		move_cursor_right(client);
	if (key == 186 && ft_strlen(keys) == 3)
		move_cursor_left(client);
	if (key == 12 && ft_strlen(keys) == 1)
	{
		ft_printf("\033[2J\033[0;0H");
		reprint_line(client, true);
	}
	if (key == 9 && ft_strlen(keys) == 1)
	{
		tab_autocomplet(client);
	}
}

void			escape_line(t_socket_client *client)
{
	size_t	cmd_len;
	int		lines;

	cmd_len = 0;
	cmd_len += ft_strlen(client->current_cmd->cmd);
	if (client->host)
		cmd_len += ft_strlen(client->host) + 2 + ft_nbrlen(client->port);
	if (client->nickname)
		cmd_len += ft_strlen(client->nickname);
	if (client->host != NULL && client->nickname != NULL)
		cmd_len += 22;
	else
		cmd_len += 8;
	if (get_size_x() < cmd_len)
	{
		lines = cmd_len / get_size_x();
		while (lines-- > 0)
			ft_printf("\033[1A\033[K");
	}
}
