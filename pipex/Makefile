OBJ = split.o pipex.o lpath.o touls.o touls1.o\

BONUSOBJ = split.o pipex_bonus.o lpath.o touls.o touls1.o here_doc_touls.o get_next_line.o get_next_line_utils.o\

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = pipex

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus : $(BONUSOBJ)
	$(CC) $(CFLAGS) $(BONUSOBJ) -o $(NAME)

clean :
	rm -f $(OBJ) $(BONUSOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

PHONY: clean