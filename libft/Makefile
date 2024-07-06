CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = libft.a
SRC = ft_atoi.c ft_bzero.c ft_calloc.c  ft_isalnum.c ft_isalpha.c
SRC += ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c
SRC += ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c
SRC += ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c
SRC += ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c
SRC += ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c
SRC += ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c 
BONUS += ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
OBJS = ${SRC:.c=.o}
BOBJS = ${BONUS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	ar rc $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

clean : 
	rm -rf ${OBJS} ${BOBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

bonus : ${BOBJS}
	ar rc ${NAME} ${BOBJS}

.PHONY : all clean fclean re bonus