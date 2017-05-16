# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/25 15:18:38 by jguyet            #+#    #+#              #
#    Updated: 2017/03/19 04:47:40 by jguyet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_p

SERVER		=	serveur

CLIENT		=	client

NAMEBASE    =   $(shell basename $(NAME) .a)

LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`

MAX_COLS	=	$$(echo "$$(tput cols)-20-$(LENGTHNAME)"|bc)

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -ggdb

SRCDIR		=

OBJDIR		=	.objs/

INCDIR		=	includes/

LIBFTDIR	=	libft/

INCDIRLIBFT	=	$(LIBFTDIR)/includes/

SRCSERVER	=	\
				srcs/server/main.c															\
				srcs/server/socket/server.c													\
				srcs/server/socket/server_handler.c											\
				srcs/server/socket/socket_accept.c											\
				srcs/server/socket/client/client.c											\
				srcs/server/socket/client/client_handler.c									\
				srcs/server/socket/client/disconnect.c										\
				srcs/server/signals/signals.c												\
				srcs/server/message/data_processor.c										\
				srcs/server/message/load_received_messages.c								\
				srcs/server/message/received/cd_message.c									\
				srcs/server/message/received/pwd_message.c									\
				srcs/server/message/received/ls_message.c									\
				srcs/server/message/received/download_file_message.c						\
				srcs/server/message/received/upload_file_message.c							\
				srcs/server/message/received/upload_part_message.c							\
				srcs/server/message/received/download_part_message.c						\
				srcs/lib_file/file_exists.c													\
				srcs/lib_file/is_regular.c													\
				srcs/lib_file/is_device.c													\
				srcs/lib_file/is_dir.c														\
				srcs/lib_file/get_file_mode.c												\
				srcs/lib_upload_download/load_new_download.c								\
				srcs/lib_upload_download/load_new_upload.c									\
				srcs/lib_upload_download/download_part.c									\
				srcs/lib_upload_download/upload_part.c										\
				srcs/lib_upload_download/size_of_parts.c

SRCSSERVER	=	$(addprefix $(SRCDIR), $(SRCSERVER))

OBJSSERVER	=	$(addprefix $(OBJDIR), $(SRCSERVER:.c=.o))

SRCCLIENT	=	\
				srcs/client/main.c															\
				srcs/client/message/data_processor.c										\
				srcs/client/prompt/command_processor.c										\
				srcs/client/prompt/command_history.c										\
				srcs/client/prompt/command_remove.c											\
				srcs/client/prompt/command_switcher.c										\
				srcs/client/prompt/prompt_putting.c											\
				srcs/client/prompt/cursor_navigation.c										\
				srcs/client/commands/exit_command.c											\
				srcs/client/message/load_received_messages.c								\
				srcs/client/message/load_send_messages.c									\
				srcs/client/message/send/cd_message.c										\
				srcs/client/message/send/pwd_message.c										\
				srcs/client/message/send/ls_message.c										\
				srcs/client/message/send/download_file_message.c							\
				srcs/client/message/send/upload_file_message.c								\
				srcs/client/message/received/infos_message.c								\
				srcs/client/message/received/directory_message.c							\
				srcs/client/message/received/upload_part_message.c							\
				srcs/client/message/received/download_part_message.c						\
				srcs/client/message/received/download_message.c								\
				srcs/client/socket/handler.c												\
				srcs/client/socket/socket.c													\
				srcs/client/socket/session.c												\
				srcs/client/socket/disconnect.c												\
				srcs/client/window/size.c													\
				srcs/client/window/termios.c												\
				srcs/lib_file/file_exists.c													\
				srcs/lib_file/is_regular.c													\
				srcs/lib_file/is_device.c													\
				srcs/lib_file/is_dir.c														\
				srcs/lib_file/get_file_mode.c												\
				srcs/lib_upload_download/load_new_download.c								\
				srcs/lib_upload_download/load_new_upload.c									\
				srcs/lib_upload_download/download_part.c									\
				srcs/lib_upload_download/upload_part.c										\
				srcs/lib_upload_download/size_of_parts.c

SRCSCLIENT	=	$(addprefix $(SRCDIR), $(SRCCLIENT))

OBJSCLIENT	=	$(addprefix $(OBJDIR), $(SRCCLIENT:.c=.o))

.SILENT:

all:
	if test -f $(CLIENT) && test -f $(SERVER) ; then										\
		echo "make: Nothing to be done for \`all\`.";										\
	else																					\
		$(MAKE) -j $(NAME);																	\
	fi

$(NAME):
	make -C $(LIBFTDIR)
	$(MAKE) $(CLIENT)
	$(MAKE) $(SERVER)

$(CLIENT):	$(OBJDIR) $(OBJSCLIENT)
	$(CC) $(FLAGS) -o $(CLIENT) $(OBJSCLIENT) -L $(LIBFTDIR) -lftprintf
	echo "MAKE   [$(CLIENT)]"

$(SERVER):	$(OBJDIR) $(OBJSSERVER)
	$(CC) $(FLAGS) -o $(SERVER) $(OBJSSERVER) -L $(LIBFTDIR) -lftprintf
	echo "MAKE   [$(SERVER)]"

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(dir $(OBJSSERVER))
	mkdir -p $(dir $(OBJSCLIENT))

$(OBJDIR)%.o : $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(FLAGS) -MMD -c $< -o $@															\
		-I $(INCDIR) -I $(INCDIRLIBFT)
	printf "\r\033[38;5;117m%s%*.*s\033[0m\033[K"											\
	"MAKE   "$(NAMEBASE)" plz wait ..."														\
		$(MAX_COLS) $(MAX_COLS) "($(@)))"

clean:
	if [[ `rm -R $(OBJDIR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then						\
		echo -en "\r\033[38;5;101mCLEAN  "													\
		"[\033[0m$(NAMEBASE)\033[38;5;101m]\033[K";											\
	else																					\
		printf "\r";																		\
	fi
	make -C $(LIBFTDIR) fclean

fclean:		clean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then							\
		echo -en "\r\033[38;5;124mFCLEAN "													\
		"[\033[0m$(NAMEBASE)\033[38;5;124m]\033[K";											\
	else																					\
		printf "\r";																		\
	fi
	make -C $(LIBFTDIR) fclean
	rm -rf $(CLIENT)
	rm -rf $(SERVER)
	rm -rf $(OBJDIR)

libre:
	make -C $(LIBFTDIR) re
	echo "lalalla"

re:			fclean all

.PHONY:		fclean clean re

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
