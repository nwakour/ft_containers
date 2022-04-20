.PHONY: 		all fclean clean re

NAME			=	a.out

SRCS			=	test.cpp

OBJS			=	${SRCS:.cpp=.o}

CC				=	c++

FLAGS           =	-fsanitize=address -g -Werror -Wextra -Wall -std=c++98 

RM				=	rm -f

all:			$(NAME)

$(NAME):	$(SRCS)
				@$(CC) $(FLAGS) -o $(NAME) $(SRCS)
				@echo "a.out was created successfully"

clean:			
				@$(RM) $(OBJS)

fclean:			
				@$(RM) $(NAME)

re:				fclean all
