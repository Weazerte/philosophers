# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weaz <weaz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 13:25:39 by eaubry            #+#    #+#              #
#    Updated: 2023/09/27 02:09:02 by weaz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =	src/main.c src/routine.c src/check.c src/ft_atoi.c src/utils.c src/init.c src/monitoring.c src/fcked_routine.c

NAME    =	philo

OBJS    =	${SRCS:.c=.o}

CFLAGS    =    -Wall -Wextra -Werror -g

CC	=	cc

all:	${NAME}

.c.o:	${INC}
	${CC} ${CFLAGS} -MMD -MP -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	${CC} ${CFLAGS} ${OBJS} -lpthread -o ${NAME} 

-include ${SRCS:.c=.d}

clean:
	rm -f ${OBJS}
	rm -f src/*.d

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re bonus