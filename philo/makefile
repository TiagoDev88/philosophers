
NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -I includes
# CFLAGS = -Wall -Wextra -Werror -pthread  -I includes


SRC_DIR = src

SRC_MAIN	=	main.c init.c start_routine.c utils.c
# SRC_MAIN	=	main_thread.c
# SRC_UTILS	=	$(addprefix utils/, utils.c)

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_MAIN) $(SRC_UTILS))

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅  $(NAME) Compiled successfully!"

clean:
	@$(RM) $(OBJS)
	@echo "clean: object files removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "fclean: executable removed"

re: fclean all

teste: re
	@./philo 5 800 200 200

teste1: re
	@./philo 5 800 200 200 3

.PHONY: all clean fclean re