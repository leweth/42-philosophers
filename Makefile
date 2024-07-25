CC = cc 

CFLAGS = -Wall -Wextra -Werror -lpthread

NAME = philo

SRCS = phio.c

OBJS = ${SRCS:.c=.o}


all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;33mBuilding Target...\033[0m"
	${CC} ${CFLAGS} $(OBJS) lib/printf/libftprintf.a -o ${NAME}
	@echo "\033[1;32mTarget Built Successfully!\033[0m"

%.o: %.c includes/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;33mRemoving Object files...\033[0m"
	rm -rf ${OBJS}

fclean: clean
	@echo "\033[1;33mRemoving libraries and program...\033[0m"
	rm -rf ${NAME}

re: fclean all