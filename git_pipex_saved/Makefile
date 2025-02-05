# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 20:47:23 by nmartin           #+#    #+#              #
#    Updated: 2025/02/03 20:22:51 by nmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[33m
GREEN = \033[32m
BLUE = \033[34m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
NAME = pipex
SRC_PATH = ./srcs/
SRC_FILES = ppx_main.c pipex.c ppx_utils.c
SRC := $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ_PATH = ./objs/
OBJ := $(addprefix $(OBJ_PATH), $(SRC_FILES:.c=.o))
SRC_BNS_PATH = ./srcs_bonus/
SRC_BNS_FILES = pipex_bonus.c pipex.c ppx_utils.c
SRC_BNS := $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ_BNS := $(addprefix $(OBJ_PATH), $(SRC_BNS_FILES:.c=.o))
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
HEADERS = -Iheaders -I$(LIBFT_PATH)
DEPS := $(OBJ:.o=.d)

all : $(NAME)

bonus : $(LIBFT) $(OBJ_BNS)
	@echo "$(BLUE)Creating $(NAME) bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

$(NAME) : $(LIBFT) $(OBJ)
	@echo "$(BLUE)Creating $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_PATH)%.o : $(SRC_BNS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT) :
	@make -C $(LIBFT_PATH) --no-print-directory

clean :
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(OBJ_PATH)
	@echo "$(YELLOW)Cleaned successfully$(RESET)"

fclean : clean
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(NAME)
	@echo "$(YELLOW)Full cleaned successfully$(RESET)"

re : fclean all

#commands perso

exec : fclean all
	@make clean --no-print-directory

.PHONY : all clean fclean re

-include $(DEPS)
