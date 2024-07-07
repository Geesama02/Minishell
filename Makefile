CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
CC = cc
NAME = minishell
SRC = main.c parsing/ft_split_env.c ft_strcmp.c parsing/fill_token.c ft_strtrim.c execution/builtins.c parsing/create_ast.c ft_strncmp.c \
	execution/execution.c expanding/expanding.c parsing/tokenizer.c parsing/tokenizer_utils.c parsing/tokenizer_utils2.c parsing/shunting_yard.c parsing/shunting_yard_utils.c \
	parsing/build_tree.c expanding/expanding_utils.c expanding/expanding_utils2.c expanding/expanding_utils3.c expanding/ft_split_one.c expanding/wildcard_utils.c execution/pipe_execution.c execution/execution_utils.c \
	execution/redirection.c expanding/wildcard_utils2.c parsing/heredoc.c parsing/heredoc_utils.c parsing/heredoc_utils2.c parsing/tokenizer_utils3.c \
	execution/builtins_utils.c ft_env_split.c expanding/expanding_env.c expanding/expanding_env_utils.c execution/heredoc_execution.c \
	signals/signals.c parsing/build_tree_utils.c execution/memory_utils.c \
	execution/builtins_failure.c execution/builtins2.c execution/execution_utils2.c
OBJS = ${SRC:.c=.o}
LIBFT = ./libft/libft.a
FT_PRINTF = ./ft_printf_err/libftprintf.a
LPATH = ../../.brew/opt/readline

all : ${NAME}
	make -C ./libft
	make bonus -C ./libft
	make -C ./ft_printf_err

${LIBFT} :
	make -C ./libft
	make bonus -C ./libft

${FT_PRINTF} :
	make -C ./ft_printf_err

${NAME} : ${OBJS} ${LIBFT} ${FT_PRINTF}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${FT_PRINTF} -lreadline -L ${LPATH}/lib -o ${NAME}

%.o: %.c parse_header.h
	${CC} ${CFLAGS} -I ${LPATH}/include -c -o $@ $<

clean :
	rm -rf ${OBJS}
	make clean -C ./libft
	make clean -C ./ft_printf_err

fclean : clean
	rm -rf ${NAME}
	make fclean -C ./libft
	make fclean -C ./ft_printf_err

re : fclean all

.PHONY : all clean fclean re bonus