.PHONY: 		all fclean clean re

NAME			=	map

SRCS			=	map_test.cpp

OBJS			=	${SRCS:.cpp=.o}

CC				=	c++

FLAGS           =	 -Werror -Wextra -Wall -std=c++98

RM				=	rm -f

all:			$(NAME)

$(NAME):	$(SRCS)
				@$(CC) $(FLAGS) -o $(NAME) $(SRCS)
				@echo "map was created successfully"

clean:			
				@$(RM) $(OBJS)

fclean:			
				@$(RM) $(NAME)

re:				fclean all
