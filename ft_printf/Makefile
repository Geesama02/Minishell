SRCS = ft_printf.c ft_putnbr.c ft_putchar.c is_string.c per_p.c per_x.c
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror


%.o : %.c ft_printf.h
	${CC} ${CFLAGS} -c $< -o $@

all : ${NAME}

${NAME} : ${OBJS}
	ar rc ${NAME} ${OBJS}

clean : 
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : re clean fclean all
