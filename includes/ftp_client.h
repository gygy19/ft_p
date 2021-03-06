/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:41:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/16 19:41:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT_H
# define FTP_CLIENT_H

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

# include "ftp_protocolmessage.h"
# include "ftp_upload.h"

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
	char				*oldhost;
	int					port;
	int					sockfd;
	char				*nickname;
	struct sockaddr_in	serv_addr;
	struct hostent		*server;
	struct s_events		events[2];
	struct s_cmds		*cmds;
	struct s_cmds		*current_cmd;
	struct s_hashmap	*messagessendmap;
	struct s_hashmap	*messagesreceivedmap;
	int					(*send)();
	char				*(*serialize)(const char *, ...);
	char				*message;
	char				*pwd;
	char				*download_directory;
	t_upload			*upload;
	t_upload			*download;
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
void					reprint_line(t_socket_client *client, BOOLEAN save);
void					print_prompt(t_socket_client *client);
void					print_current_command(t_socket_client *client,\
						int start);

/*
** Commands send
*/
void					load_command_pointer(t_socket_client *client);
BOOLEAN					cd_message(t_socket_client *client, char **split);
BOOLEAN					pwd_message(\
						t_socket_client *client, char **split);
BOOLEAN					ls_message(\
						t_socket_client *client, char **split);
BOOLEAN					download_file_message(\
						t_socket_client *client, char **split);
BOOLEAN					upload_file_message(\
						t_socket_client *client, char **split);
BOOLEAN					exit_command(t_socket_client *client,\
						char **split);
BOOLEAN					help_command(t_socket_client *client,\
						char **split);
BOOLEAN					reconnect_command(t_socket_client *client,\
						char **split);
BOOLEAN					connect_command(t_socket_client *client,\
						char **split);
BOOLEAN					disconnect_command(t_socket_client *client,\
						char **split);
BOOLEAN					set_download_path_command(t_socket_client *client,\
						char **split);
BOOLEAN					get_download_path_command(t_socket_client *client,\
						char **split);

# define AR_CMD_SIZE 13

static const t_protocolmessage g_arrayprotocolmessagessend[AR_CMD_SIZE] = {
	{"cd", 100, cd_message, true},
	{"pwd", 101, pwd_message, true},
	{"ls", 102, ls_message, true},
	{"get", 103, download_file_message, true},
	{"put", 104, upload_file_message, true},
	{"quit", 0, exit_command, true},
	{"exit", 0, exit_command, true},
	{"help", 0, help_command, true},
	{"reconnect", 0, reconnect_command, true},
	{"connect", 0, connect_command, true},
	{"disconnect", 0, disconnect_command, true},
	{"setdownloadpath", 0, set_download_path_command, true},
	{"getdownloadpath", 0, get_download_path_command, true}
};

/*
** Messages Received
*/
void					load_received_messages(t_socket_client *client);
BOOLEAN					infos_message(t_socket_client *client,\
						char *message);
BOOLEAN					directory_message(t_socket_client *client,\
						char *message);
BOOLEAN					upload_part_message(t_socket_client *client,\
						char *message);
BOOLEAN					download_part_message(t_socket_client *client,\
						char *message);
BOOLEAN					download_message(t_socket_client *client,\
						char *message);
BOOLEAN					hello_message(t_socket_client *client,\
						char *message);

# define AR_RCV_SIZE 6

static const t_protocolmessage g_arrayprotocolmessagesreceived[AR_RCV_SIZE] = {
	{"InfosMessage", 12, infos_message, true},
	{"DirectoryInfos", 13, directory_message, true},
	{"getPartUpload", 14, upload_part_message, false},
	{"DownloadPart", 104, download_part_message, false},
	{"DownloadFile", 103, download_message, false},
	{"HelloMessage", 1, hello_message, false}
};

/*
** Window
*/
size_t					get_size_x(void);
size_t					get_size_y(void);

#endif
