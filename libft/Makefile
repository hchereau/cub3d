NAME = libft.a

### SRCS #######################################################################

PATH_SRCS = srcs/libft/

SRCS += ft_isalpha.c
SRCS += ft_isdigit.c
SRCS += ft_isalnum.c
SRCS += ft_isascii.c
SRCS += ft_isprint.c
SRCS += ft_strlen.c
SRCS += ft_memset.c
SRCS += ft_bzero.c
SRCS += ft_memcpy.c
SRCS += ft_memmove.c
SRCS += ft_strlcpy.c
SRCS += ft_strlcat.c
SRCS += ft_toupper.c
SRCS += ft_tolower.c
SRCS += ft_strchr.c
SRCS += ft_strrchr.c
SRCS += ft_strncmp.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_strnstr.c
SRCS += ft_atoi.c
SRCS += ft_calloc.c
SRCS += ft_strdup.c
SRCS += ft_substr.c
SRCS += ft_strjoin.c
SRCS += ft_strtrim.c
SRCS += ft_split.c
SRCS += ft_itoa.c
SRCS += ft_strmapi.c
SRCS += ft_striteri.c
SRCS += ft_putchar_fd.c
SRCS += ft_putstr_fd.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr_fd.c
SRCS += ft_lstnew_bonus.c
SRCS += ft_lstadd_front_bonus.c
SRCS += ft_lstadd_back_bonus.c
SRCS += ft_lstsize_bonus.c
SRCS += ft_lstlast_bonus.c
SRCS += ft_lstdelone_bonus.c
SRCS += ft_lstclear_bonus.c
SRCS += ft_lstmap_bonus.c
SRCS += ft_lstiter_bonus.c
SRCS += ft_abs.c
SRCS += ft_atoi_base.c
SRCS += ft_atol.c
SRCS += ft_strslen.c
SRCS += ft_strcmp.c
SRCS += ft_realloc.c

vpath %.c $(PATH_SRCS)

### GET_NEXT_LINE ##############################################################

PATH_SRCS_GNL = srcs/gnl/

SRCS_GNL += get_next_line.c
SRCS_GNL += get_next_line_utils.c

vpath %.c $(PATH_SRCS_GNL)

### PRINTF #####################################################################

PATH_SRCS_PRINTF = srcs/printf/

SRCS_PRINTF += add_to_file_string.c
SRCS_PRINTF += ft_dprintf.c
SRCS_PRINTF += ft_uitoa.c
SRCS_PRINTF += utils_buffer.c
SRCS_PRINTF += utils_num.c
SRCS_PRINTF += utils_pointeur.c
SRCS_PRINTF += utils_string.c
SRCS_PRINTF += utils.c

vpath %.c $(PATH_SRCS_PRINTF)

### HEADER #####################################################################

INCLUDES_LIBFT = includes/

INCLUDES += -I $(INCLUDES_LIBFT)

HEADER += $(INCLUDES_LIBFT)/libft.h

### OBJS #######################################################################

PATH_OBJS = objs/

 OBJS += $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))
 OBJS += $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS_GNL))
 OBJS += $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS_PRINTF))

### COMPILATION ################################################################

CC = clang
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -Wall

AR = ar

ifeq ($(debug), true)
		CFLAGS += -fsanitize=address,undefined -g3
endif

### TEST #######################################################################

TEST_FOLDER = libft_tester/
RUN_TESTS = $(TEST_FOLDER)/run_test

### RULE #######################################################################

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) rcs $@ $^

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADER)
		mkdir -p $(PATH_OBJS)
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

bonus: $(NAME)

# test: $(NAME)
# 		$(MAKE) -sC $(TEST_FOLDER)
# 		echo -n "\n<--------TESTS-------->\n\n"
# 		./$(RUN_TESTS);

clean:
		$(RM) -r $(PATH_OBJS)
#		$(MAKE) -C $(TEST_FOLDER) clean

fclean: clean
		$(RM) $(NAME)
#		$(MAKE) -C $(TEST_FOLDER) fclean

re: fclean
		$(MAKE)

.PHONY: all bonus clean fclean re
.SILENT: test
