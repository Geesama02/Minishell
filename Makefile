CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
CC = cc
NAME = minishell
SRC = main.c ft_split.c ft_strcmp.c ft_strjoin.c fill_token.c ft_strtrim.c builtins.c create_ast.c ft_strncmp.c ft_strdup.c \
	execution.c expanding.c tokenizer.c tokenizer_utils.c tokenizer_utils2.c shunting_yard.c shunting_yard_utils.c \
	build_tree.c expanding_utils.c ft_split_one.c wildcard_utils.c pipe_execution.c execution_utils.c wildcard_utils2.c
OBJS = ${SRC:.c=.o}
LIBFT = ./libft/libft.a
PATH = ../../.brew/opt/readline

all : ${NAME}

${LIBFT} :
	cd ./libft && make

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -L ${PATH}/lib -o ${NAME}

%.o: %.c parse_header.h
	${CC} ${CFLAGS} -I ${PATH}/include -c -o $@ $<

clean : 
	rm -rf ${OBJS}
	cd ./libft && make clean

fclean : clean
	rm -rf ${NAME}
	cd ./libft && make fclean

re : fclean all

.PHONY : all clean fclean re bonus