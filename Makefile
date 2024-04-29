CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CC = cc
NAME = main
SRC = main.c ft_split.c ft_strcmp.c ft_strjoin.c fill_token.c ft_strtrim.c \
builtins.c
OBJS = ${SRC:.c=.o}
LIBFT = ./libft/libft.a

all : ${NAME}

${LIBFT} :
	cd ./libft && make

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

%.o: %.c parse_header.h
	${CC} ${CFLAGS} -c -o $@ $<

clean : 
	rm -rf ${OBJS} ${BOBJS}
	cd ./libft && make clean

fclean : clean
	rm -rf ${NAME}
	cd ./libft && make fclean

re : fclean all

.PHONY : all clean fclean re bonus