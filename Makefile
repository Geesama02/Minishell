CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
CC = cc
NAME = minishell
SRC = main.c main_utils.c main_utils2.c execution/ft_atoi_long.c execution/exit_utils.c expanding/export_utils.c expanding/expanding_utils5.c execution/execution_utils3.c expanding/expanding_utils4.c execution/redirection_utils.c execution/unset_utils.c execution/function_protections.c parsing/ft_split_qt.c parsing/ft_env_split.c parsing/ft_env_split_no_qt.c parsing/ft_strcmp.c parsing/fill_token.c execution/builtins.c parsing/create_ast.c \
	execution/execution.c expanding/expanding.c parsing/tokenizer.c parsing/tokenizer_utils.c parsing/tokenizer_utils2.c parsing/shunting_yard.c parsing/shunting_yard_utils.c \
	parsing/build_tree.c expanding/expanding_utils.c expanding/expanding_utils2.c expanding/expanding_utils3.c expanding/ft_split_one.c expanding/wildcard_utils.c execution/pipe_execution.c execution/execution_utils.c \
	execution/redirection.c expanding/wildcard_utils2.c parsing/heredoc.c parsing/heredoc_utils.c parsing/heredoc_utils2.c parsing/heredoc_utils3.c  parsing/tokenizer_utils3.c \
	execution/builtins_utils.c expanding/expanding_env.c expanding/expanding_env_utils.c execution/heredoc_execution.c \
	signals/signals.c parsing/build_tree_utils.c execution/memory_utils.c parsing/tokenizer_utils4.c parsing/tokenizer_utils5.c parsing/tokenizer_utils6.c parsing/tokenizer_utils7.c \
	execution/builtins_failure.c execution/builtins2.c execution/execution_utils2.c 
OBJS = ${SRC:.c=.o}
LIBFT = ./libft/libft.a
LPATH = ../../.brew/opt/readline

all : ${NAME}

${LIBFT} :
	make -C ./libft
	make bonus -C ./libft

${NAME} : ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -L ${LPATH}/lib -o ${NAME}

%.o: %.c parse_header.h
	${CC} ${CFLAGS} -I ${LPATH}/include -c -o $@ $<

clean :
	rm -rf ${OBJS}
	make clean -C ./libft

fclean : clean
	rm -rf ${NAME}
	make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re bonus
