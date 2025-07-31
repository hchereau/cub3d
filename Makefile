.RECIPEPREFIX = >
NAME = cub3D

### LIBFT #####################################################################

PATH_LIBFT := libft/

LIBFT := $(PATH_LIBFT)libft.a

### MINILIBX ###################################################################

MINILIBX_FOLDER := minilibx-linux/
LIB_MLX := $(MINILIBX_FOLDER)/libmlx.a

### SRCS #######################################################################

PATH_SRCS += srcs/
PATH_SRCS += srcs/parse/
PATH_SRCS += srcs/exec/

SRCS += main.c

# srcs/parse/

SRCS += parse.c
SRCS += file_reader.c
SRCS += parse_utils.c
SRCS += texture.c
SRCS += color.c
SRCS += map.c
SRCS += validate_map.c
SRCS += error.c

# srcs/exec/

SRCS += exec_game.c
SRCS += hooks.c
SRCS += image.c
SRCS += raycast.c
SRCS += player_init.c
SRCS += player_movement.c
SRCS += raycast_utils.c
SRCS += ray_init.c
SRCS += ray_wall.c

vpath %.c $(PATH_SRCS)

### OBJS #######################################################################

PATH_OBJS := objs/

OBJS := $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

### HEADERS ####################################################################

PATH_INCLUDES := includes/
PATH_INCLUDES_LIBFT := $(PATH_LIBFT)/includes/
PATH_INCLUDES_MLX := $(MINILIBX_FOLDER)/

### COMPILATION ################################################################

CC := clang

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

### LINKING ####################################################################

LINKS += -Lmlx-linux
LINKS += -L/usr/lib
LINKS += -lXext
LINKS += -lX11
LINKS += -lm
LINKS += -lz
LINKS += -fPIE

### COLORS #####################################################################

GREEN := \033[0;32m
BLUE := \033[0;34m
WHITE := \033[0;37m

### RULE #######################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(LIB_MLX) $(OBJS)
> @echo "$(BLUE)Compiling $(NAME)...$(WHITE)"
> @$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_MLX) $(LIBFT) $(LINKS) -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT) -I $(MINILIBX_FOLDER)
> @echo "$(GREEN)$(NAME) Compiled !$(WHITE)"

$(OBJS): $(PATH_OBJS)%.o: %.c
> @mkdir -p $(dir $@)
> @$(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT) -I $(MINILIBX_FOLDER)

$(LIBFT):
> @echo "$(BLUE)Compiling $(LIBFT) ...$(WHITE)"
> @$(MAKE) -sC $(PATH_LIBFT)
> @echo "$(GREEN)$(LIBFT) Compiled ! $(WHITE)"

$(LIB_MLX):
> @echo "$(BLUE)Compiling $(LIB_MLX) ...$(WHITE)"
> @$(MAKE) -sC $(MINILIBX_FOLDER)
> @echo "$(GREEN)$(LIB_MLX) Compiled !$(WHITE)"

clean:
> @echo "$(BLUE)Cleaning $(NAME) ...$(WHITE)"
> @$(RM) -r objs
> @$(MAKE) -sC libft clean
> -@$(MAKE) -sC $(MINILIBX_FOLDER) clean
> @echo "$(GREEN)$(NAME) Cleaned ! $(WHITE)"

fclean: clean
> @echo "$(BLUE)Full Cleaning $(NAME) ...$(WHITE)"
> @$(RM) $(NAME)
> @$(MAKE) -sC $(PATH_LIBFT) fclean
> -@$(MAKE) -sC $(MINILIBX_FOLDER) clean
> @echo "$(GREEN)$(NAME) Fully Cleaned ! $(WHITE)"

re: fclean all

.PHONY: all clean fclean re
