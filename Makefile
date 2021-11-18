# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 17:03:23 by ctirions          #+#    #+#              #
#    Updated: 2021/11/18 04:29:54 by ctirions         ###   ########.fr        #
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
				init.c			\
				actions.c		\

OBJS		=	$(addprefix srcs/, ${SRCS:.c=.o})

NAME		=	philo.a
EXEC		=	philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
PFLAGS		=	-pthread

.c.o:
				@${CC} ${CFLAGS} ${PFLAGS} -g -c -I ./includes $< -o ${<:.c=.o}
				@echo "${LIGHTPURPLE}Compilation : $< --> .o${RESET}"

$(NAME):		${OBJS}
				@ar -rcs ${NAME} ${OBJS}
				@${CC} ${CFLAGS} ${PFLAGS} -g ${NAME} -o ${EXEC}
				
all:			${NAME}
				
clean:			
				@rm -f ${OBJS}
				@echo "${RED}Clean done !${RESET}"

fclean:			clean
				@rm -f ${NAME} ${EXEC}
				@echo "${RED}Fclean done !${RESET}"

re:				fclean all

.PHONY:			all clean fclean bonus re