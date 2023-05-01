NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror -lreadline
CC = cc
RM = rm -rf
SCRS = 

LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)
INC = -I ./includes

$(NAME): $(SCRS) $(LIBFT)
	@echo "Compiling Minishell..."
	$(CC) $(CFLAGS) $(INC) $(SCRS) -o $(NAME)
	@echo "Minishell compiled!"

$(LIBFT):
	@echo "Compiling libft..."
	@make -sC $(LIBFT_PATH)
	@echo "libft compiled!"

all: $(LIBFT) $(NAME)

clean:
	$(RM) $(NAME)

fclean: 
	make fclean -sC $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
