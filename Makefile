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
				srcs/server/main.c																					\
				srcs/server/data_processor.c																\
				srcs/server/lib/server.c																		\
				srcs/server/lib/handler.c																		\
				srcs/server/lib/socket_accept.c															\
				srcs/server/lib/sig.c																				\
				srcs/server/client/client.c																	\
				srcs/server/client/client_aks.c															\
				srcs/server/message/loadProtocolsMessagesReceived.c					\
				srcs/server/message/received/cdProtocolMessage.c						\
				srcs/server/message/received/pwdProtocolMessage.c						\
				srcs/server/message/received/lsProtocolMessage.c						\
				srcs/server/message/received/getFileProtocolMessage.c				\
				srcs/server/message/received/putFileProtocolMessage.c				\
				srcs/server/message/received/DownloadPartProtocolMessage.c	\
				srcs/xor/xor.c																							\
				srcs/xor/hexa_xor.c																					\
				srcs/libfile/file_exists.c																	\
				srcs/libfile/is_regular.c																		\
				srcs/libfile/isdevice.c																			\
				srcs/libfile/isdir.c																				\
				srcs/libUpDownload/loadnewDownload.c												\
				srcs/libUpDownload/loadnewUpload.c													\
				srcs/libUpDownload/downloadPart.c														\
				srcs/libUpDownload/uploadPart.c															\
				srcs/libUpDownload/sizesOfParts.c														\
				srcs/server/lib/socket_disconnect.c

SRCSSERVER	=	$(addprefix $(SRCDIR), $(SRCSERVER))

OBJSSERVER	=	$(addprefix $(OBJDIR), $(SRCSERVER:.c=.o))

SRCCLIENT	=	\
				srcs/client/main.c																					\
				srcs/client/data_processor.c																\
				srcs/client/prompt/command_processor.c											\
				srcs/client/prompt/command_history.c												\
				srcs/client/prompt/command_remove.c													\
				srcs/client/prompt/command_switcher.c												\
				srcs/client/prompt/prompt_putting.c													\
				srcs/client/prompt/cursor_navigation.c											\
				srcs/client/commands/CommandLoader.c												\
				srcs/client/commands/quitCommand.c													\
				srcs/client/message/loadProtocolsMessagesReceived.c					\
				srcs/client/message/send/cdProtocolMessage.c								\
				srcs/client/message/send/pwdProtocolMessage.c								\
				srcs/client/message/send/lsProtocolMessage.c								\
				srcs/client/message/send/getFileProtocolMessage.c						\
				srcs/client/message/send/putFileProtocolMessage.c						\
				srcs/client/message/received/textProtocolMessage.c					\
				srcs/client/message/received/directoryProtocolMessage.c			\
				srcs/client/message/received/getPartUploadProtocolMessage.c	\
				srcs/client/lib/handler.c																		\
				srcs/client/lib/socket.c																		\
				srcs/client/window/size.c																		\
				srcs/client/window/termios.c																\
				srcs/xor/xor.c																							\
				srcs/xor/hexa_xor.c																					\
				srcs/libfile/file_exists.c																	\
				srcs/libfile/is_regular.c																		\
				srcs/libfile/isdevice.c																			\
				srcs/libfile/isdir.c																				\
				srcs/libUpDownload/loadnewDownload.c												\
				srcs/libUpDownload/loadnewUpload.c													\
				srcs/libUpDownload/downloadPart.c														\
				srcs/libUpDownload/uploadPart.c															\
				srcs/libUpDownload/sizesOfParts.c														\
				srcs/client/lib/socket_session.c

SRCSCLIENT	=	$(addprefix $(SRCDIR), $(SRCCLIENT))

OBJSCLIENT	=	$(addprefix $(OBJDIR), $(SRCCLIENT:.c=.o))

.SILENT:

all:
	if test -f $(CLIENT) && test -f $(SERVER) ; then						\
		echo "make: Nothing to be done for \`all\`.";						\
	else																	\
		$(MAKE) -j $(NAME);													\
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
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(INCDIR) -I $(INCDIRLIBFT)
	printf "\r\033[38;5;117m%s%*.*s\033[0m\033[K"							\
	"MAKE   "$(NAMEBASE)" plz wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@)))"

clean:
	if [[ `rm -R $(OBJDIR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo -en "\r\033[38;5;101mCLEAN  "									\
		"[\033[0m$(NAMEBASE)\033[38;5;101m]\033[K";							\
	else																	\
		printf "\r";														\
	fi
	make -C $(LIBFTDIR) fclean

fclean:		clean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo -en "\r\033[38;5;124mFCLEAN "									\
		"[\033[0m$(NAMEBASE)\033[38;5;124m]\033[K";							\
	else																	\
		printf "\r";														\
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
