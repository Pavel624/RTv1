NAME = RTv1

SRC_FILES  = main.c keys.c color.c sphere.c plane.c light_op.c cylinder.c cone.c validation_objects.c \
			help_valid.c ray.c shape_utils.c vector3_op.c vector3_op2.c
SRC_FOLDER = ./sources
INC_FOLDER = ./includes
SRC = $(addprefix $(SRC_FOLDER)/, $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FOLDER = ./objs
OBJ = $(addprefix $(OBJ_FOLDER)/, $(OBJ_FILES))

OSVER := $(shell uname -s)

ifeq ($(OSVER), Linux)
	LIBFLAGS = -L/usr/X11/lib /usr/X11/lib/libmlx.a -g3 -lXext -lX11 -lm -lmlx
	FLAGS = -Wall -Werror -Wextra -O2
else
	LIBFLAGS = -framework OpenGL -framework AppKit -lmlx
	FLAGS = -Wall -Werror -Wextra -O2
endif

LIBFT = libft/libft.a

INC_LIB = libft

HEAD = libft/libft.h

RED= \033[1;31m
GREEN= \033[1;32m
YELLOW= \033[1;33m
BLUE= \033[1;34m
VIOLET= \033[1;35m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GREEN)Compiling project$(VIOLET)"
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(LIBFLAGS) -I$(INC_LIB) -o $(NAME)
	@echo "$(GREEN)Project is successfully compiled$(VIOLET)"

$(LIBFT):
	@echo "$(GREEN)Compiling object files$(VIOLET)"
	@make -C libft/

$(OBJ_FOLDER)/%.o : $(SRC_FOLDER)/%.c
	@mkdir -p $(OBJ_FOLDER)
	gcc $(FLAGS) -c $< -o $@ -I $(INC_LIB) -I$(INC_FOLDER)

clean:
	@echo "$(RED)Suspending library object files$(VIOLET)"
	@make -C libft clean
	@echo "$(RED)Suspending object files$(VIOLET)"
	rm -f $(OBJ)
	rm -rf $(OBJ_FOLDER)

fclean: clean
	@echo "$(RED)Suspending library files$(VIOLET)"
	@make -C libft fclean
	@echo "$(RED)Suspending project files$(VIOLET)"
	rm -f $(OBJ)
	rm -rf $(OBJ_FOLDER)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
