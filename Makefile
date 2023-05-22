NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror -lreadline
CC = cc
RM = rm -rf

#SRCS	= 	$(addprefix $(SRC_PATH), $(SRC))
OBJS	= 	$(SRC:.c=.o)
#OBJS	= 	$(addprefix $(OBJ_PATH), $(OBJ))

SRCS =		minishell.c \
			src/signals/signals.c \

LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)
INC = -I ./includes

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

all: $(LIBFT) $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRCS) $(LIBFT)
	@echo "Compiling Minishell..."
	@$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME)
	@echo "Minishell compiled!"

$(LIBFT):
	@echo "Compiling libft..."
	@make -sC $(LIBFT_PATH)
	@echo "libft compiled!"

clean:
	@make clean -sC $(LIBFT_PATH)
	@$(RM) $(OBJS)
	@echo "Deleted .o files"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@$(RM) $(NAME)
	@echo "Deleted executable"

re: fclean all

.PHONY: all clean fclean re
