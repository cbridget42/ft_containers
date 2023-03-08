NAME = ft_containers
OBJ_FOLDER = objects
FLAGS = -Wall -Wextra -Werror -Wshadow -Wno-shadow -fsanitize=address -std=c++98 -g3
CC = c++

S_PATH = sources/
H_PATH = headers/
I_PATH = templates/iterators
V_PATH = templates/vector
ST_PATH = templates/stack

HEADERS = $(wildcard $(addsuffix /*.hpp,$(H_PATH)))
TEMPLATES = $(wildcard $(addsuffix /*.tpp,$(I_PATH))) \
$(wildcard $(addsuffix /*.tpp,$(V_PATH))) $(wildcard $(addsuffix /*.tpp,$(ST_PATH)))
OBJ = $(addprefix $(OBJ_FOLDER)/,$(notdir $(SRC:.cpp=.o)))
SRC = $(wildcard $(addsuffix /*.cpp,$(S_PATH)))

BUILD_FOLDERS := $(shell mkdir -p $(OBJ_FOLDER))

.PHONY : all clean fclean bonus re

all : $(NAME)

bonus : all

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_FOLDER)/%.o : sources/%.cpp $^ $(HEADERS) $(TEMPLATES) Makefile
	$(CC) $(FLAGS) -iquote headers -iquote templates/stack -iquote templates/vector -iquote templates/iterators -c $< -o $@

clean :
	rm -rf $(OBJ_FOLDER)

fclean :
	rm -rf $(OBJ_FOLDER)
	rm -f $(NAME)

re :
	rm -rf $(OBJ_FOLDER)/*.o
	rm -f $(NAME)
	$(MAKE)