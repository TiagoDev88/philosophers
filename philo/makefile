
NAME = philo

CC = cc
CFLAGS =  -I includes -Wall -Wextra -Werror

SRC_DIR = src

SRC_MAIN	=	main.c
SRC_UTILS	=	$(addprefix utils/, utils.c)

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

.PHONY: all clean fclean re