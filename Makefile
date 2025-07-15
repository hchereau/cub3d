NAME = cub3D


### LIBFT ######################################################################

PATH_LIBFT := libft/

LIBFT := $(PATH_LIBFT)libft.a

### SRCS #######################################################################

PATH_SRCS += srcs/

SRCS += main.c

### HEADER #####################################################################

PATH_INCLUDES := includes/
PATH_INCLUDES_LIBFT := $(PATH_LIBFT)includes/

### COMPILATION ################################################################

CC = clang

CFLAGS += -Wall
CFLAGS += -Wextra
CLFAGS += -Werror

### OBJS #######################################################################

PATH_OBJS := objs/

OBJS := $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

### COLOR ######################################################################

GREEN := \033[0;32m
BLUE := \033[0;34m
WHITE := \033[0;37m

### RULES ######################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@echo "$(BLUE)Compiling $(NAME) ...$(WHITE)"
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT)
		@echo "$(GREEN)$(NAME) Compiled !$(WHITE)"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADERS)
		@mkdir -p $(PATH_OBJS)
		@$(CC) $(CFLAGS) -c $< -o -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT)

$(LIBFT):
		@echo "$(BLUE)Compiling $(LIBFT) ...$(WHITE)"
		@$(MAKE) -sC $(PATH_LIBFT)
		@echo "$(GREEN)$(LIBFT) Compiled ! $(WHITE)"

clean:
	@echo "$(BLUE)Cleaning $(NAME) ...$(WHITE)"
	@$(RM) -r $(PATH_OBJS)
	@$(MAKE) -sC $(PATH_LIBFT) clean
	@echo "$(GREEN)$(NAME) Cleaned ! $(WHITE)"

fclean: clean
	@echo "$(BLUE)Full Cleaning $(NAME) ...$(WHITE)"
	@$(RM) $(NAME)
	@$(MAKE) -sC $(PATH_LIBFT) fclean
	@echo "$(GREEN)$(NAME) Fully Cleaned ! $(WHITE)"

re: fclean all

.PHONY: all clean fclean re
