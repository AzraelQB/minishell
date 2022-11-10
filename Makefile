NAME = 	minishell
HEADER = minishell.h
FILES = srcs/utils/ft_utils1.c\
  		srcs/utils/ft_utils2.c\
		srcs/utils/ft_utils3.c\
		srcs/utils/ft_utils4.c\
  		srcs/utils/lst_utils.c\
		srcs/utils/lst_utils2.c\
		srcs/utils/ft_split.c\
		srcs/mem_funcs.c\
		srcs/builtins/ft_cd.c\
		srcs/builtins/ft_echo.c\
		srcs/builtins/ft_env.c\
		srcs/builtins/ft_exit.c\
		srcs/builtins/ft_export.c\
		srcs/builtins/ft_pwd.c\
		srcs/builtins/ft_unset.c\
		srcs/error_handling.c\
		srcs/parse_cmd.c\
		srcs/executor.c\
		srcs/minishell.c

OBJS		= $(FILES:.c=.o)
CC			= gcc
CFLAGS		= -I includes/ #-Wall -Wextra -Werror 
NONE		= '\033[0m'
GREEN		= '\033[32m'

.PHONY: all clean fclean bonus

%.o :		%.c Makefile $(HEADER)
			@$(CC) $(CFLAGS) -c $< -o $@
			
all: 		$(NAME)


$(NAME) : 	$(OBJS)
			@gcc $(CFLAGS) -o $(NAME) $(OBJS)
			@echo $(GREEN)"- all ready -"$(NONE)

clean:
			@rm -rf $(OBJS)
			@echo $(GREEN)"- objs cleaned -"$(NONE)

fclean : 	clean
			@rm -rf $(NAME)
			@echo $(GREEN)"- all cleaned  -"$(NONE)

re: fclean all