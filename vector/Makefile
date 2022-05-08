.PHONY: 		all fclean clean re

NAME			=	vector

SRCS			=	vector_test.cpp

OBJS			=	${SRCS:.cpp=.o}

CC				=	c++

FLAGS           =	 -Werror -Wextra -Wall -std=c++98

RM				=	rm -f

all:			$(NAME)

$(NAME):	$(SRCS)
				@$(CC) $(FLAGS) -o $(NAME) $(SRCS)
				@echo "vector was created successfully"

clean:			
				@$(RM) $(OBJS)

fclean:			
				@$(RM) $(NAME)

re:				fclean all
