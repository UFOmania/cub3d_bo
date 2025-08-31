NAME = cub3D
LIBMLX = lib/libmlx42.a
LIBFT = lib/libft.a
FLAGS = -Wall -Wextra -Werror

SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$ cc $(FLAGS) $(OBJS) $(LIBMLX) $(LIBFT) -lglfw -framework Cocoa -framework OpenGL -framework IOKit  -o $(NAME)

%.o: %.c
	 cc $(FLAGS) -o $@ -c $<  && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all