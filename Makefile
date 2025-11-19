INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= cub3d

SRC_DIR= src

FULL_SRC= $(addprefix $(SRC_DIR)/, $(SRC) )

SRC = main.c nextline/get_next_line.c nextline/get_next_line_utils.c main_utl.c error.c map_data.c mlx_init.c cub3d.c draw.c dda.c movement.c textures.c free.c map_data1.c dda_init.c

LIBFT = libft.a

OBJ = $(FULL_SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= cc
	LFLAGS += -lbsd
endif

all: $(NAME)

$(LIBFT):
		cd ./libft && make
		cd ./libft && mv libft.a "../"
		cd ./libft && make fclean

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)
    
clean:
	rm -f $(NAME) $(OBJ) $(LIBFT) *~ core *.core
fclean:		clean
					rm -rf $(NAME) $(LIBFT)
	
re: clean all

.PHONY: all clean fclean re