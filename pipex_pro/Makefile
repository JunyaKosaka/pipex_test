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
#                     process0 process1
	./${NAME} small.txt "cat" "hedad -n 4" file
#                   filefd  pipe0
	wc file

test: fclean retest

heretest: ${NAME}
	./${NAME} here_doc aaa cat "head -n 2" "tail -n 1" wc file
	cat file

here: fclean heretest

PHONY: fclean clean all re test retest
