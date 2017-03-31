/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:41:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/16 19:41:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CLIENT_H
# define IRC_CLIENT_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <termios.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <printf.h>
# include <mapft.h>
# include <unistd.h>
# include <netdb.h>

# define EPROTONOSUPPORT 93
# define EAFNOSUPPORT    97

# define PROT_INTERNET_IPV4 AF_INET
# define PROT_INTERNET_IPV6 AF_INET6

# define BINARY_SOCK_FLUX SOCK_STREAM
# define NON_BLOCK_SOCK_FLUX 04000

# define DEFAULT_PROTOCOL 0

# define SOL_TCP 6

# define TCP_KEEPCNT 5
# define TCP_KEEPIDLE 5
# define TCP_KEEPINTVL 1

# define MODE_DEBUG 1

typedef struct			s_events
{
	int					fd;
	void				(*read)();
}						t_events;

typedef struct			s_cmds
{
	char				*cmd;
	struct s_cmds		*right;
	struct s_cmds		*left;
	size_t				cursor_pos;
}						t_cmds;

typedef struct			s_socket_client
{
	char				*host;
	int					port;
	int					sockfd;
	char				*nickname;
	struct sockaddr_in	serv_addr;
	struct hostent		*server;
	struct s_events		events[2];
	struct s_cmds		*cmds;
	struct s_cmds		*current_cmd;
	int					(*send)();
	char				*(*serialize)(const char *, ...);
	char				*message;
}						t_socket_client;

/*
** Socket
*/
int						open_socket_connection(t_socket_client *client,\
						char *formated_ip, int port);
int						aks_initialize_connection(t_socket_client *client);
int						send_message(t_socket_client *client, char *message);
void					received_message(t_socket_client *client);
int						client_handler(t_socket_client *client);
void					server_disconnect(t_socket_client *client);

/*
** Prog client
*/
int						load_termios_console(void);
void					data_processor(t_socket_client *client, char *message);

/*
** Prompt command
*/
void					read_keys(t_socket_client *client);
t_cmds					*new_command(t_socket_client *client);
void					switch_command(t_socket_client *client, char *cmd);

/*
** cursor_nav
*/
void					move_cursor_to_keycode_dir(t_socket_client *client,\
						int key, char *keys);
void					del_one_entry(t_socket_client *client);
void					escape_line(t_socket_client *client);

/*
** history
*/
void					up_to_next_olded_command(t_socket_client *client);
void					down_to_olded_next_command(t_socket_client *client);
void					use_history_command(t_socket_client *client);

/*
** prompt
*/
void					restart_line(void);
void					reprint_line(t_socket_client *client);
void					print_prompt(t_socket_client *client);
void					print_current_command(t_socket_client *client,\
						int start);

/*
** Window
*/
size_t					get_size_x(void);
size_t					get_size_y(void);

#endif
