# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 17:09:58 by aet-tass          #+#    #+#              #
#    Updated: 2023/06/11 23:56:26 by aet-tass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo_utils_1.c philosophers.c store_args.c
OBJ = ${SRC:.c=.o}

NAME = philo

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

RM = rm -f

AR = ar -rc

CC = cc

%.o:%.c
	${CC} -g -c $<

all : ${NAME}

${NAME}: ${OBJ}
	 ${CC} $(CFLAGS) ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
