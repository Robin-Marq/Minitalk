# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 10:14:18 by rmarquar          #+#    #+#              #
#    Updated: 2024/02/12 16:34:43 by rmarquar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
OBJ_DIR = obj

SRC_C = client.c
OBJ_C = $(addprefix $(OBJ_DIR)/, $(SRC_C:.c=.o))

SRC_S = server.c
OBJ_S = $(addprefix $(OBJ_DIR)/, $(SRC_S:.c=.o))

CFLAGS = -Wall -Wextra -Werror
LIB = -L./ft_printf -lftprintf -L./libft -lft

CC = cc

# ANSI-Farbcodes for the output
RED		= \033[31m
GREEN	= \033[32m
Yellow	= \033[33m
BLUE	= \033[34m
MAGENTA	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
RESET	= \033[0m

all: $(NAME)

$(NAME): $(OBJ_S) $(OBJ_C)
	@make -C ./ft_printf
	@make -C ./libft
	@$(CC) -o server $(OBJ_S) $(CFLAGS) $(LIB)
	@$(CC) -o client $(OBJ_C) $(CFLAGS) $(LIB)
	@clear
	@echo "$(GREEN)\nServer and Client are ready! Have fun :-)\n$(RESET)"

# creating a fresh folder for the object files (only if it not exist)
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# compile the object files and save it into the "obj folder"
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C ./ft_printf clean
	@make -C ./libft clean

fclean: clean
	@rm -f server client
	@rm -f ./ft_printf/libftprintf.a
	@rm -f ./libft/libft.a
	@clear
	@echo "$(BLUE)\nServer and Client have been cleaned successfully. Thank you and bye bye :-)\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re