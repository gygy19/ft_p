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

NAME		=	FT_P

PROG		=	ft_p

LENGTHNAME	=	`printf "%s" $(NAME) | wc -c`

MAX_COLS	=	$$(echo "$$(tput cols)-20-$(LENGTHNAME)"|bc)

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -ggdb

SRCDIR		=	

OBJDIR		=	.objs/

INCDIR		=	includes/

LIBFTDIR	=	libft/

INCDIRLIBFT	=	$(LIBFTDIR)/includes/

SRC			=	\
				srcs/main.c

SRCS		=	$(addprefix $(SRCDIR), $(SRC))

OBJS		=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

.SILENT:

all:
	if test -f $(PROG) && test -f $(SERVER) ; then						\
		echo "make: Nothing to be done for \`all\`.";						\
	else																	\
		$(MAKE) -j $(NAME);													\
	fi

$(NAME):
	make -C $(LIBFTDIR)
	$(MAKE) $(PROG)

$(PROG):	$(OBJDIR) $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS) -L $(LIBFTDIR) -lftprintf
	echo "MAKE   [$(NAME)]"

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(dir $(OBJS))

$(OBJDIR)%.o : $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(INCDIR) -I $(INCDIRLIBFT)
	printf "\r\033[38;5;117m%s%*.*s\033[0m\033[K"							\
	"MAKE   "$(NAME)" plz wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@)))"

clean:
	if [[ `rm -R $(OBJDIR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo -en "\r\033[38;5;101mCLEAN  "									\
		"[\033[0m$(NAME)\033[38;5;101m]\033[K";							\
	else																	\
		printf "\r";														\
	fi
	make -C $(LIBFTDIR) fclean

fclean:		clean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo -en "\r\033[38;5;124mFCLEAN "									\
		"[\033[0m$(NAME)\033[38;5;124m]\033[K";							\
	else																	\
		printf "\r";														\
	fi
	make -C $(LIBFTDIR) fclean
	rm -rf $(PROG)
	rm -rf $(OBJDIR)

re:			fclean all

.PHONY:		fclean clean re

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
