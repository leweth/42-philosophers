CC = cc 

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

NAME = philo

SRCS = philo.c srcs/ft_atou32.c srcs/input_processing.c srcs/print_error.c srcs/init_utils.c srcs/clean_utils.c \
		srcs/action_utils.c

OBJS = ${SRCS:.c=.o}


all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;33mBuilding Target...\033[0m"
	${CC} ${CFLAGS} -lpthread $(OBJS) -o ${NAME}
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