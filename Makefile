# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 17:09:58 by aet-tass          #+#    #+#              #
#    Updated: 2023/06/04 17:12:14 by aet-tass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =
OBJ = ${SRC:.c=.o}

NAME = 

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar -rc

CC = cc

%.o:%.c
        ${CC} ${CFLAGS} -c $<

all : ${NAME}

${NAME}: ${OBJ}
        ${AR} ${NAME} ${OBJ}

clean:
        ${RM} ${OBJ}

fclean: clean
        ${RM} ${NAME}

re: fclean all

.PHONY:         all clean fclean re
