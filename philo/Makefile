NAME = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./inc
SRC_PATH = src/
OBJ_PATH = obj/

SRCS = 	$(SRC_PATH)/basic_utils.c \
	$(SRC_PATH)/dinner.c \
	$(SRC_PATH)/init.c \
	$(SRC_PATH)/main.c \
	$(SRC_PATH)/monitoring.c \
	$(SRC_PATH)/parse.c \
	$(SRC_PATH)/routine.c \
	$(SRC_PATH)/special_utils.c \


SRC	= $(addprefix $(SRC_PATH), $(SRCS))
OBJ = $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re