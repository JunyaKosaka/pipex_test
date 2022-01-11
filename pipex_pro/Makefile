NAME		= pipex

SRCS		= pipex.c cmd_full_path.c start_process.c \
			get_next_line.c get_next_line_utils.c \
			valid_utils.c error_handler.c \

OBJS		= $(SRCS:%.c=%.o)

LIBFT		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
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
	./${NAME} pipex.h cat "head -xxn 3" file
	cat file

test: fclean retest

heretest: ${NAME}
	./${NAME} here_doc aaa cat "head -n 2" "tail -n 1" wc file
	cat file

here: fclean heretest

PHONY: fclean clean all re test retest
