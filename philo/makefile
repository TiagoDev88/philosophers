
NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -I includes
# CFLAGS = -Wall -Wextra -Werror -pthread  -I includes


SRC_DIR = src
SRC_OBJ = obj

SRC_MAIN	=	main.c init.c start_routine.c utils.c utils_start_routine.c
# SRC_MAIN	=	main_thread.c
# SRC_UTILS	=	$(addprefix utils/, utils.c)

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_MAIN) $(SRC_UTILS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(SRC_OBJ)/%.o)

RM = rm -rf

all: $(NAME)

$(SRC_OBJ)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(SRC_OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅  $(NAME) Compiled successfully!"

clean:
	@$(RM) $(SRC_OBJ)
	@echo "clean: object files removed"

fclean: clean
	@$(RM) $(NAME) $(SRC_OBJ)
	@echo "fclean: executable removed"

re: fclean all

teste: re
	@./philo 5 800 200 200

teste1: re
	@./philo 5 800 200 200 3

.PHONY: all clean fclean re