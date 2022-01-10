NAME		= pipex

SRCS		= pipex.c cmd_full_path.c

OBJS		= $(SRCS:%.c=%.o)

LIBFT		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

retest: ${NAME}
	./${NAME} pipex.h cat "head -n 4" "tail -n 2" file

test: fclean retest

PHONY: fclean clean all re test retest
