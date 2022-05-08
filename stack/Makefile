.PHONY: 		all fclean clean re

NAME			=	stack

SRCS			=	stack_test.cpp

OBJS			=	${SRCS:.cpp=.o}

CC				=	c++

FLAGS           =	 -Werror -Wextra -Wall -std=c++98

RM				=	rm -f

all:			$(NAME)

$(NAME):	$(SRCS)
				@$(CC) $(FLAGS) -o $(NAME) $(SRCS)
				@echo "stack was created successfully"

clean:			
				@$(RM) $(OBJS)

fclean:			
				@$(RM) $(NAME)

re:				fclean all
