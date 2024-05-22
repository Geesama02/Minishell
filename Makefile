CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
CC = cc
NAME = minishell
SRC = main.c ft_split.c ft_strcmp.c parsing/fill_token.c ft_strtrim.c execution/builtins.c parsing/create_ast.c ft_strncmp.c \
	execution/execution.c expanding/expanding.c parsing/tokenizer.c parsing/tokenizer_utils.c parsing/tokenizer_utils2.c parsing/shunting_yard.c parsing/shunting_yard_utils.c \
	parsing/build_tree.c expanding/expanding_utils.c expanding/ft_split_one.c wildcard_utils.c execution/pipe_execution.c execution/execution_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	execution/redirection.c
OBJS = ${SRC:.c=.o}
LIBFT = ./libft/libft.a
NEXT_LINE_H = ./get_next_line/get_next_line.h


all : ${NAME}

${LIBFT} :
	make -C libft

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

%.o: %.c parse_header.h ${NEXT_LINE_H}
	${CC} ${CFLAGS} -c -o $@ $<

clean :
	rm -rf ${OBJS} ${BOBJS}
	make clean -C libft

fclean : clean
	rm -rf ${NAME}
	make fclean -C libft

re : fclean all

.PHONY : all clean fclean re bonus