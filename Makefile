NAME = ft_containers
OBJ_FOLDER = objects
FLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++

S_PATH = sources/
H_PATH = headers/
T_PATH = templates/

HEADERS = $(wildcard $(addsuffix /*.hpp,$(H_PATH)))
TEMPLATES = $(wildcard $(addsuffix /*.tpp,$(T_PATH)))
OBJ = $(addprefix $(OBJ_FOLDER)/,$(notdir $(SRC:.cpp=.o)))
SRC = $(wildcard $(addsuffix /*.cpp,$(S_PATH)))

BUILD_FOLDERS := $(shell mkdir -p $(OBJ_FOLDER))

.PHONY : all clean fclean bonus re

all : $(NAME)

bonus : all

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_FOLDER)/%.o : sources/%.cpp $^ $(HEADERS) $(TEMPLATES) Makefile
	$(CC) $(FLAGS) -iquote headers -iquote templates -c $< -o $@

clean :
	rm -rf $(OBJ_FOLDER)

fclean :
	rm -rf $(OBJ_FOLDER)
	rm -f $(NAME)

re :
	rm -rf $(OBJ_FOLDER)/*.o
	rm -f $(NAME)
	$(MAKE)