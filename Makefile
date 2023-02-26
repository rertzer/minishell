CC = gcc
FLAGS = -Wall -Wextra -Werror -g

NAME = minishell

LIBFT_DIR = libft/

SRC_DIR = src/

OBJ_DIR = obj/

INC_DIR = includes/

LIBFT = $(LIBFT_DIR)libft.a

SOURCES = dollar.c \
	env.c \
	line.c \
	parsing.c \
	pipe.c \
	split.c \
	utils.c \
	minishell.c \
	lpid.c \
#	r_test.c \

OBJ = $(SOURCES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME) $(BONUS_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR) 

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -o  $@ $(OBJS) $(LIBFT) -lreadline

$(OBJ_DIR):
	mkdir  $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean: miniclean
	make -C $(LIBFT_DIR) clean

miniclean:
	rm -f $(OBJS)
	rm -fd $(OBJ_DIR)

fclean: miniclean 
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

minifclean: miniclean
	rm -f $(NAME)

re: fclean all

minire : minifclean all

.PHONY: all bonus clean fclean miniclean minifclean re minire
