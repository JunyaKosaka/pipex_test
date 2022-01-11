NAME		= pipex

SRCS		= pipex.c cmd_full_path.c start_process.c \
			get_next_line.c get_next_line_utils.c

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
	make clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

retest: ${NAME}
	./${NAME} pipex.h cat "head -n 4" "tail -n 2" file

test: fclean retest

PHONY: fclean clean all re test retest
