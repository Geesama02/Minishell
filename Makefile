CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = main
SRC = main.c ft_split.c ft_strcmp.c ft_strjoin.c fill_token.c ft_strtrim.c \
builtins.c
OBJS = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -lreadline -o ${NAME}

%.o: %.c parse_header.h
	${CC} ${CFLAGS} -c -o $@ $<

clean : 
	rm -rf ${OBJS} ${BOBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re bonus