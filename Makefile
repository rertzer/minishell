CC = gcc
FLAGS = -Wall -Wextra -Werror -g3

NAME = minishell

LIBFT_DIR = libft/

SRC_DIR = src/

OBJ_DIR = obj/

INC_DIR = includes/

LIBFT = $(LIBFT_DIR)libft.a

SOURCES = args.c \
	args_parse.c \
	backtrack.c \
	builtin.c \
	cd.c \
	cd_utils.c \
	char.c \
	check_cmd.c \
	child.c \
	command.c \
	dollar.c \
	echo.c \
	env.c \
	exit.c \
	export.c \
	file.c \
	file_utils.c \
	here_doc.c \
	open.c \
	output.c \
	parsing.c \
	pipe.c \
	pipeline.c \
	pwd.c \
	redirect.c \
	return.c \
	return_null.c \
	run.c \
	sort.c \
	split.c \
	tfile.c \
	trim.c \
	unset.c \
	utils_pp.c \
	utils.c \
	minishell.c \
	lpid.c \
	lpid_del.c \
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
