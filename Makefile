.RECIPEPREFIX = >
NAME = cub3D
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRCS = \
 srcs/main.c \
 srcs/parse/parse.c \
 srcs/parse/file_reader.c \
 srcs/parse/parse_utils.c \
 srcs/parse/texture.c \
 srcs/parse/color.c \
 srcs/parse/map.c \
 srcs/parse/validate_map.c \
 srcs/parse/error.c
OBJS = $(SRCS:%.c=objs/%.o)
LIBFT = libft/libft.a
INCLUDES = -I includes -I libft/includes

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
> $(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(INCLUDES)

objs/%.o: %.c
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT):
> $(MAKE) -C libft

clean:
> rm -rf objs
> $(MAKE) -C libft clean

fclean: clean
> rm -f $(NAME)
> $(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
