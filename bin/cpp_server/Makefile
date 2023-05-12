##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## programmers start to count from 0
##

CXX	=	g++

SRC	=	$(shell find src -name "*.cpp")

OBJ	=	$(SRC:.cpp=.o)

NAME	=	../launch_server

CXXFLAGS	=	-W -Wall -Wextra -Werror -std=c++20

all:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
