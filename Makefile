NAME = ircserv

SRC =  main.cpp channel.cpp client.cpp server.cpp  \
	commands/Command.cpp commands/join.cpp commands/privmsg.cpp commands/list.cpp commands/checks.cpp commands/quit.cpp

OBJ_DIR = obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98

all: $(NAME)

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(@D)
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

