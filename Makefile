NAME_STACK = stack
NAME_VECTOR = vector
NAME_MAP = map

NAME_VECTOR_STD = vector_std
NAME_MAP_STD = map_std
NAME_STACK_STD = stack_std

HEADERS_FILE = vector.hpp stack.hpp map.hpp

CLANG= clang++
VALGRIND_FLAGS = -ggdb3
FLAGS= -Wall -Wextra -Werror -std=c++98 -ggdb3

HEADERS = \
			stack.hpp \
			vector.hpp \
			map.hpp \
			avl/avl_tree.hpp \
			avl/avl_node.hpp \
			utils.hpp \
			iterators/iterator_traits.hpp \
			iterators/random_access_iterator.hpp \
			iterators/reverse_iterator.hpp \
			iterators/map_iterator.hpp

SRC_VECTOR = srcs/main_vector.cpp
SRC_STACK = srcs/main_stack.cpp
SRC_MAP = srcs/main_map.cpp

OBJ_STACK = ${SRC_STACK:.cpp=.o}
OBJ_VECTOR = ${SRC_VECTOR:.cpp=.o}
OBJ_MAP = ${SRC_MAP:.cpp=.o}

OBJ_MAP_STD = $(SRC_MAP:.cpp=_std.o)
OBJ_STACK_STD = $(SRC_STACK:.cpp=_std.o)
OBJ_VECTOR_STD = $(SRC_VECTOR:.cpp=_std.o)

STACK_LOG = stack_valgrind.log
VECTOR_LOG = vector_valgrind.log
MAP_LOG = map_valgrind.log

all:  $(NAME_STACK) $(NAME_VECTOR) $(NAME_MAP) $(NAME_MAP_STD) $(NAME_VECTOR_STD) $(NAME_STACK_STD)

valgrind: $(NAME_STACK) $(NAME_VECTOR) $(NAME_MAP) $(NAME_MAP_STD) $(NAME_VECTOR_STD) $(NAME_STACK_STD)
	@echo "valgrind stack"
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=$(STACK_LOG)  ./$(NAME_STACK)
	@echo "valgrind vector"
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=$(VECTOR_LOG) ./$(NAME_VECTOR)
	@echo "valgrind map"
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=$(MAP_LOG) ./$(NAME_MAP)

##############################################
$(NAME_STACK): $(OBJ_STACK) $(HEADERS)
	$(CLANG) $(OBJ_STACK) -o $(NAME_STACK)

$(NAME_STACK_STD): $(OBJ_STACK_STD) $(HEADERS)
	$(CLANG) $(VALGRIND_LEAKS) $(OBJ_STACK_STD) -o $(NAME_STACK_STD)

$(NAME_VECTOR): $(OBJ_VECTOR) $(HEADERS)
	$(CLANG) $(OBJ_VECTOR) -o $(NAME_VECTOR)

$(NAME_VECTOR_STD): $(OBJ_VECTOR_STD) $(HEADERS)
	$(CLANG) $(VALGRIND_LEAKS) $(OBJ_VECTOR_STD) -o $(NAME_VECTOR_STD)

$(NAME_MAP): $(OBJ_MAP) $(HEADERS)
	$(CLANG)  $(OBJ_MAP) -o $(NAME_MAP)

$(NAME_MAP_STD): $(OBJ_MAP_STD) $(HEADERS)
	$(CLANG) $(VALGRIND_LEAKS) $(OBJ_MAP_STD) -o $(NAME_MAP_STD)

##############################################

$(OBJ_STACK): %.o: %.cpp $(HEADERS)
	$(CLANG)  -Wall -Wextra -Werror -std=c++98 -c $< -o $@

$(OBJ_STACK_STD): $(SRC_STACK) $(HEADERS)
	$(CLANG) -Wall -Wextra -Werror -std=c++98 -c $< -o $@ -D USING_STD=1

$(OBJ_VECTOR): %.o: %.cpp $(HEADERS)
	$(CLANG)  -Wall -Wextra -Werror -std=c++98 -c $< -o $@

$(OBJ_VECTOR_STD): $(SRC_VECTOR) $(HEADERS)
	$(CLANG)  -Wall -Wextra -Werror -std=c++98 -c $< -o $@ -D USING_STD=1

$(OBJ_MAP): %.o: %.cpp $(HEADERS)
	$(CLANG) -Wall -Wextra -Werror -std=c++98 -c $< -o $@

$(OBJ_MAP_STD): $(SRC_MAP) $(HEADERS)
	$(CLANG)  -Wall -Wextra -Werror -std=c++98 -c $< -o $@ -D USING_STD=1

clean:
	rm -f $(OBJ_STACK) $(OBJ_VECTOR) $(OBJ_MAP) $(OBJ_MAP_STD) $(OBJ_VECTOR_STD) $(OBJ_STACK_STD)

fclean: clean
	rm -f $(NAME_STACK) $(NAME_VECTOR) $(NAME_MAP) $(NAME_MAP_STD) $(NAME_VECTOR_STD) $(NAME_STACK_STD) $(STACK_LOG) $(VECTOR_LOG) $(MAP_LOG)

re: fclean all

.PHONY: all clean fclean re