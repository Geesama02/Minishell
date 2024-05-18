CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
CC = cc
NAME = minishell
SRC = main.c ft_split.c ft_strcmp.c fill_token.c ft_strtrim.c builtins.c create_ast.c ft_strncmp.c \
	execution.c expanding.c tokenizer.c tokenizer_utils.c tokenizer_utils2.c shunting_yard.c shunting_yard_utils.c \
	build_tree.c expanding_utils.c ft_split_one.c pipe_execution.c execution_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = ${SRC:.c=.o}
LIBFT = ./libft/libft.a
NEXT_LINE_H = ./get_next_line/get_next_line.h


all : ${NAME}

${LIBFT} :
	cd ./libft && make 

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

%.o: %.c parse_header.h ${NEXT_LINE_H}
	${CC} ${CFLAGS} -c -o $@ $<

clean : 
	rm -rf ${OBJS} ${BOBJS}
	cd ./libft && make clean

fclean : clean
	rm -rf ${NAME}
	cd ./libft && make fclean

re : fclean all

.PHONY : all clean fclean re bonus