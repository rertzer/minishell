CC = gcc
FLAGS = -Wall -Wextra -Werror -g3

NAME = minishell

LIBFT_DIR = libft/

SRC_DIR = src/

OBJ_DIR = obj/

INC_DIR = includes/

LIBFT = $(LIBFT_DIR)libft.a

SOURCES = args.c \
	builtin.c \
	cd.c \
	cd_utils.c \
	char.c \
	check_cmd_bonus.c \
	child_bonus.c \
	command.c \
	dollar.c \
	echo.c \
	env.c \
	exit.c \
	export.c \
	file.c \
	file_utils.c \
	here_doc_bonus.c \
	parsing.c \
	pattern.c \
	pipe.c \
	pipeline.c \
	pipexrun.c \
	pwd.c \
	return.c \
	run_bonus.c \
	tfile.c \
	trim.c \
	unset.c \
	utils_bonus.c \
	utils.c \
	pipex.c \
	minishell.c \
	lpid.c \
	signal.c \
	wildcard.c

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
