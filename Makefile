INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= cub3d

SRC = main.c nextline/get_next_line.c nextline/get_next_line_utils.c main_utl.c error.c map_data.c mlx_init.c algorithm.c draw.c

LIBFT = libft.a

OBJ = $(SRC:%.c=%.o)

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
	rm -f $(NAME) $(OBJ) *~ core *.core
fclean:		clean
					rm -rf $(NAME)
	
re: clean all

.PHONY: all clean fclean re