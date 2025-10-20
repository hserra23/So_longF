# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hserra <hserra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 14:42:59 by hserra            #+#    #+#              #
#    Updated: 2025/10/20 15:40:31 by hserra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
PARSE_DIR = parsing_and_validation
GAME_DIR = game
LIBFT_DIR = libft
MLX_DIR = mlx_linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Flags
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INC = -I$(PARSE_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR)

# Source files
PARSE_SRCS = $(PARSE_DIR)/main.c \
             $(PARSE_DIR)/map_parsing.c \
             $(PARSE_DIR)/map_parsing_utils.c \
             $(PARSE_DIR)/map_validation.c \
             $(PARSE_DIR)/map_validation_utils.c \
             $(PARSE_DIR)/utils_parsing.c \
			 $(PARSE_DIR)/map_validation_p2.c \

GAME_SRCS = $(GAME_DIR)/game_init.c \
            $(GAME_DIR)/render.c \
            $(GAME_DIR)/player_movement.c \
            $(GAME_DIR)/game_close.c \

SRCS = $(PARSE_SRCS) $(GAME_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "✓ so_long compiled successfully!"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "✓ Object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "✓ Executable removed"

re: fclean all

.PHONY: all clean fclean re