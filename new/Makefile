NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror -lreadline
CC = cc
RM = rm -rf

SRCS =	main.c \
		src/buildin/buildin_1.c \
		src/buildin/buildin_2_echo.c \
		src/buildin/buildin_3_export.c \
		src/buildin/buildin_4_cd.c \
		src/buildin/buildin_5_exit.c \
		src/buildin/buildin_6_pwd.c \
		src/buildin/buildin_7_unset.c \
		src/buildin/buildin_8_env.c \
		src/lexer/lexer_1.c \
		src/lexer/lexer_2.c \
		src/lexer/lexer_3.c \
		src/lexer/lexer_4.c \
		src/parser/parse_multi_env.c \
		src/parser/parse_multi_env_2.c \
		src/parser/parser_1.c \
		src/parser/parser_2.c \
		src/parser/parser_3.c \
		src/signals/signals.c \
		src/utils/debug.c \
		src/utils/env.c \
		src/utils/error.c \
		src/utils/expand.c \
		src/utils/free_1.c \
		src/utils/free_2.c \

OBJS	= 	$(SRC:.c=.o)

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