.RECIPEPREFIX = >
NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_strlen.c ft_strdup.c ft_strncmp.c ft_strchr.c \
 ft_calloc.c ft_memcpy.c ft_memset.c ft_atoi.c ft_split.c ft_isdigit.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
> ar rcs $(NAME) $(OBJS)

clean:
> rm -f $(OBJS)

fclean: clean
> rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
