NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror
#CFLAGS	:= -g3 -fsanitize=address -Wall -Wextra -Werror
CC = cc
RM = rm -rf

SRCS =		src/main.c \
			src/signals/signals.c \
			src/builtin/buildin_1.c \
			src/builtin/buildin_2_echo.c \
			src/builtin/buildin_2_echo2.c \
			src/builtin/buildin_3_export.c \
			src/builtin/buildin_3_export2.c \
			src/builtin/buildin_4_cd.c \
			src/builtin/buildin_4_cd2.c \
			src/builtin/buildin_5_exit.c \
			src/builtin/buildin_6_pwd.c \
			src/builtin/buildin_7_unset.c \
			src/builtin/buildin_8_env.c \
			src/execute/execute_easy_mode.c \
			src/execute/execute_pipe_1.c \
			src/execute/execute_pipe_2.c \
			src/execute/execute_redir.c \
			src/execute/expand.c \
			src/lexer/lexer_1.c \
			src/lexer/lexer_2.c \
			src/lexer/lexer_3.c \
			src/lexer/lexer_4.c \
			src/lexer/lexer_5.c \
			src/lexer/lexer_6.c \
			src/lexer/lexer_7.c \
			src/parser/parse_multi_env_1.c \
			src/parser/parse_multi_env_2.c \
			src/parser/parse_multi_env_3.c \
			src/parser/parser_1.c \
			src/parser/parser_2.c \
			src/parser/parser_3.c \
			src/parser/parser_4.c \
			src/utils/debug.c \
			src/utils/env.c \
			src/utils/error.c \
			src/utils/free_1.c \
			src/utils/free_2.c \

OBJS	= 	$(SRC:.c=.o)


LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

all: $(LIBFT) $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRCS) $(LIBFT)
	@echo "Compiling Minishell..."
	@$(CC) $(CFLAGS) $(SRCS) libft/libft.a -lreadline -o $(NAME)
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
