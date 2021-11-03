# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 17:03:23 by ctirions          #+#    #+#              #
#    Updated: 2021/11/03 17:41:22 by ctirions         ###   ########.fr        #
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

SRCS		=	philosophers.c \
				utils.c			\

OBJS		=	$(addprefix srcs/, ${SRCS:.c=.o})

NAME		=	philosophers.a
EXEC		=	philosophers

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

.c.o:
				@${CC} ${CFLAGS} -c -I ./includes $< -o ${<:.c=.o}
				@echo "${LIGHTPURPLE}Compilation : $< --> .o${RESET}"

$(NAME):		${OBJS}
				@ar -rcs ${NAME} ${OBJS}
				@ranlib ${NAME}
				@${CC} ${CFLAGS} ${NAME} -o ${EXEC}
				
all:			${NAME}
				
clean:			
				@rm -f ${OBJS}
				@echo "${RED}Clean done !${RESET}"

fclean:			clean
				@rm -f ${NAME} ${EXEC}
				@echo "${RED}Fclean done !${RESET}"

re:				fclean all

.PHONY:			all clean fclean bonus re