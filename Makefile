# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 18:52:39 by vcarrara          #+#    #+#              #
#    Updated: 2024/12/11 11:53:10 by vcarrara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

NAME = philo
CFLAGS = -Wextra -Wall -Werror -g3 -fsanitize=thread
INCLUDE = -I ./include

SRC = src/args_check.c \
		src/aux.c \
		src/dinner.c \
		src/handlers.c \
		src/init.c \
		src/main.c \
		src/monitor.c \
		src/setup.c \
		src/threads_check.c \
		src/utils.c

OBJ = obj

SRCOBJ = $(SRC:%.c=$(OBJ)/%.o)

TOTAL_SRCS = $(words $(SRC))
COMPILED_SRCS = 0

all: $(NAME)

$(NAME): $(SRCOBJ)
	@cc $(CFLAGS) $(SRCOBJ) -o $(NAME)
	@echo "$(GREEN)Compiled.$(NC)"

${OBJ}/%.o: %.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@$(eval COMPILED_SRCS = $(shell echo $$(($(COMPILED_SRCS) + 1))))
	@echo "$(BLUE)Progress: $(shell echo "scale=2; ($(COMPILED_SRCS) / $(TOTAL_SRCS)) * 100" | bc)%$(NC)"

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)Cleaned philo objects.$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Cleaned philo.$(NC)"

re: fclean all

.PHONY: all clean fclean re
