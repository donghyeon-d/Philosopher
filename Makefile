CXX = c++
CXXFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = ./src/DiningRule.cpp ./src/Fork.cpp ./src/Main.cpp ./src/Monitor.cpp \
./src/Parser.cpp ./src/Philo.cpp ./src/Printer.cpp ./src/Timer.cpp

OBJECT = $(SRC:.cpp=.o)
HEADER_DIR = ./include

all : $(NAME)

$(NAME) : $(OBJECT)
	$(CXX) $(CXXFLAGS) $(OBJECT) -o $(NAME)

clean :
	rm -rf $(OBJECT)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY : all clean fclean re bonus
