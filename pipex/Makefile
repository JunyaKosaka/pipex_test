NAME		= pipex

SRCS		= pipex.c cmd_full_path.c start_process.c \
			get_next_line.c get_next_line_utils.c \
			valid_utils.c error_handler.c \
			free.c safe_system_call.c \

OBJS		= $(SRCS:%.c=%.o)

LIBFT		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address -g3

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
# make -C ./libft
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
	./${NAME} small.txt cat "head -n 4" "tail -n 2" file2
#						0		1			2
# wc file2

test: fclean retest

heretest: ${NAME}
	./${NAME} here_doc aaa "cat -e" "head -n 4" "tail -n 3" file
#								0		1			2
	cat file

here: fclean heretest

PHONY: fclean clean all re test retest
