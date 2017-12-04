NAME = libvector.a

FLAGS = -Wall -Wextra -Werror

HEAD = -I libvector.h 

SRC_PATH = resources/

SRC_NAME = libvector.c libvector2.c

SRC_LIBVECTOR = $(addprefix $(SRC_PATH), $(SRC_NAME))

SRCO_LIBVECTOR = $(SRC_LIBVECTOR:%.c=%.o)

all: $(NAME)

$(NAME): $(SRCO_LIBVECTOR)
	@ar rc $(NAME) $(SRCO_LIBVECTOR)
	@ranlib $(NAME)

%.o: %.c
	@gcc $(FLAGS) -c -o $@ $< $(HEAD)

clean:
	@ rm -f $(SRCO_LIBVECTOR)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all