NAME = PmergeMe
CXX = c++
# CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I./inc
CXXFLAGS = -std=c++17 -I./inc

VPATH = ./src

SRCS = main.cpp PmergeMe.cpp utils.cpp algo_vector.cpp algo_deque.cpp
OBJS_DIR = objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	@echo "Creating $(OBJS_DIR) directory"
	@mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all