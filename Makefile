NAME = RTv1

FLAGS = -Wall -Wextra -Werror 

HEAD = -I rtv1.h  lib_vector/libvector.h

SRC_RTV1_PATH = resources/

SRC_NAME_RTV1 = main.c intersection.c obj_intersection.c rotation.c additional.c

SRC_RTV1 = $(addprefix $(SRC_RTV1_PATH), $(SRC_NAME_RTV1))

SRCO_RTV1 = $(SRC_RTV1:%.c=%.o)

RED = \033[0;31m

GREEN = \033[0;32m

NC = \033[0m

all: $(NAME)
	@echo "${GREEN}-->Project compile<--${NC}"

$(NAME): $(SRCO_RTV1)
	@make -C lib_vector/
	@echo "${GREEN}^^Vector library compile^^${NC}"
	@gcc -o $(NAME) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $(SRCO_RTV1) lib_vector/libvector.a

%.o: %.c
	@gcc -c $(FLAGS) -o $@ $<
	
clean:
	@make clean -C ./lib_vector/
	@ rm -f $(SRCO_RTV1)
	@echo "${RED}Object files are delete${NC}"

fclean: clean
	@make fclean -C ./lib_vector/
	@ rm -rf $(NAME)
	@echo "${RED}Binari file delete${NC}"

re: fclean all
