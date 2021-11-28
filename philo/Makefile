# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 17:03:23 by ctirions          #+#    #+#              #
#    Updated: 2021/11/28 13:46:58 by ctirions         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		=	$(shell tput -Txterm setaf 0)
RED			=	$(shell tput -Txterm setaf 1)
GREEN		=	$(shell tput -Txterm setaf 2)
YELLOW		=	$(shell tput -Txterm setaf 3)
LIGHTPURPLE	=	$(shell tput -Txterm setaf 4)
PURPLE		=	$(shell tput -Txterm setaf 5)
BLUE		=	$(shell tput -Txterm setaf 6)
WHITE		=	$(shell tput -Txterm setaf 7)
RESET		=	$(shell tput -Txterm sgr0)

SRCS		=	philosophers.c	\
				utils.c			\
				utils2.c		\
				init.c			\
				actions.c		\

OBJS		=	$(addprefix srcs/, ${SRCS:.c=.o})

NAME		=	philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
PFLAGS		=	-pthread

.c.o:
				@${CC} ${CFLAGS} ${PFLAGS} -c -I ./includes $< -o ${<:.c=.o}
				@echo "[${LIGHTPURPLE}✡${RESET}] $< --> .o$ "

$(NAME):		${OBJS}
				@${CC} ${OBJS} ${CFLAGS} ${PFLAGS} -o ${NAME}
				@echo "[${GREEN}✡${RESET}] ${NAME} created"
				
all:			${NAME}
				
clean:			
				@rm -f ${OBJS}
				@echo "[${RED}✡${RESET}] Clean done !"

fclean:			clean
				@rm -f ${NAME}
				@echo "[${RED}✡${RESET}] Fclean done !${RESET}"

re:				fclean all

.PHONY:			all clean fclean bonus re