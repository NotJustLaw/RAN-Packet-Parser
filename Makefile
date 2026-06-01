NAME = ran_parser
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinc -g
OBJ_DIR = objs
SRC = main.cpp parser.cpp
OBJ = $(SRC:.cpp=.o)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(OBJ))

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re