/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:41:56 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/16 19:41:57 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_SERVER_H
# define FTP_SERVER_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <printf.h>
# include <mapft.h>
# include <unistd.h>

# include "ftp_protocolmessage.h"
# include "ftp_upload.h"

# define EPROTONOSUPPORT 93
# define EAFNOSUPPORT    97

# define PROT_INTERNET_IPV4 AF_INET
# define PROT_INTERNET_IPV6 AF_INET6

# define BINARY_SOCK_FLUX SOCK_STREAM

# define DEFAULT_PROTOCOL 0

# define DEBUG_MODE 1

typedef struct				s_client
{
	int						fd;
	struct s_client			*right;
	struct s_client			*left;
	struct s_client			*(*next)();
	int						(*read)();
	int						(*send)();
	char					*(*serialize)(const char *, ...);
	char					*message;
	size_t					packetlength;
	struct sockaddr_in		in;
	char					*pwd;
	char					*oldpwd;
	char					*home;
	t_upload				*upload;
	t_upload				*download;
}							t_client;

typedef struct				s_socket_server
{
	int						port;
	int						listenfd;
	int						connfd;
	char					*pwd;
	struct sockaddr_in		serv_addr;
	int						(*data_processor)();
	int						(*send_message_to_all)();
	struct s_client			*(*socket_accept)();
	struct s_client			*(*socket_disconnect)();
	struct s_client			*clients;
	struct s_hashmap		*messagesreceivedmap;
}							t_socket_server;

/*
** Prog server
*/
int							data_processor(t_socket_server *server,\
							t_client *client, char *message);

/*
** Socket_server
*/
int							socket_initialize(t_socket_server *server);
t_client					*socket_accept(t_socket_server *server, int fd,\
							struct sockaddr_in *addr);
t_client					*socket_disconnect(t_socket_server *server,\
							t_client *client);
int							socket_handler(t_socket_server *server);
int							send_message_to_all(t_socket_server *server,\
							char *message);
t_socket_server				*singleton_socket_server(int port);

/*
** Client
*/
t_client					*next_client(t_client *current);
t_client					*add_new_client(t_socket_server *server, int fd);
int							send_message(t_client *client, char *message);
int							received_message(t_socket_server *server,\
							t_client *client);

/*
** Messages received
*/
BOOLEAN						cd_message(\
							t_socket_server *server, t_client *client,\
							char *message);
BOOLEAN						pwd_message(\
							t_socket_server *server, t_client *client,\
							char *message);
BOOLEAN						ls_message(\
							t_socket_server *server, t_client *client,\
							char *message);
BOOLEAN						download_file_message(\
							t_socket_server *server, t_client *client,\
							char *message);
BOOLEAN						upload_file_message(\
							t_socket_server *server, t_client *client,\
							char *message);
BOOLEAN						upload_part_message(\
							t_socket_server *server, t_client *client,\
							char *message);
BOOLEAN						download_part_message(\
							t_socket_server *server, t_client *client,\
							char *message);

# define AR_RCV_SIZE 7

static const t_protocolmessage g_arrayprotocolmessagesreceived[AR_RCV_SIZE] = {
	{"cd", 100, cd_message, 0},
	{"pwd", 101, pwd_message, 0},
	{"ls", 102, ls_message, 0},
	{"get", 103, download_file_message, 0},
	{"put", 104, upload_file_message, 0},
	{"UploadPart", 105, upload_part_message, 0},
	{"getDownloadPart", 106, download_part_message, 0}
};

void						load_received_messages(t_socket_server *server);

#endif
