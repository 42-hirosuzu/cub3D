# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 09:52:44 by hirosuzu          #+#    #+#              #
#    Updated: 2024/06/03 21:58:18 by hirosuzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
SRCS	=	main.c raycasting.c player.c

OBJS = $(SRCS:.c=.o)
LIBFTDIR = Libft/
LIBFTNAME = libft.a
MLX42DIR = MLX42/
MLX42NAME = libmlx42.a
LIBFT = $(LIBFTDIR)$(LIBFTNAME)
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
# CFLAGS = -g -fsanitize=address
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTNAME) $(MLX42)
	# $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTNAME) -Imlx -lmlx -framework OpenGL -framework AppKit
	# $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTNAME)  -lft -L$(MLX42)/build -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
	# $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -L$(MLX42DIR)/build -lmlx42 -I$(MLX42DIR)/include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -L$(MLX42DIR)/build -lmlx42 -I$(MLX42DIR)/include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

$(LIBFTNAME): 
	make -C $(LIBFTDIR) 
	cp $(LIBFT) ./

$(MLX42):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42DIR)
	cd $(MLX42DIR) && cmake -B build && cmake --build build -j4

# $(PRINTFNAME): 
# 	make -C $(PRINTFDIR)
# 	cp $(PRINTF) ./

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make clean -C $(LIBFTDIR)
	# make clean -C $(PRINTFDIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(LIBFTNAME)
	# $(RM) $(PRINTF)
	# $(RM) $(PRINTFNAME)
	$(RM) $(NAME)

re: fclean all

# main:
# 	cc -g -fsanitize=address -Imlx -lmlx -framework OpenGL -framework AppKit Libft/*.c printf/*.c *.c

.PHONY: all clean fclean re


