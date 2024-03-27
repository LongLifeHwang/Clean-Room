CC = gcc
FLAG = -Wall -Wextra -Werror
NAME = clean_room
SOURCE = ./main.c \
		./iot/dust_check.c \
		./iot/iot_main.c \
		./utils/ft_split.c 
INC = ./clean_room.h
all : $(NAME)

$(NAME): $(SOURCE)
	$(CC) -o $(NAME) $(SOURCE) -lwiringPi

.PHONY : clean fclean re all
clean : 
	rm -f $(OBJS)

fclean :
	rm -f $(OBJS)
	rm -f $(NAME)

re :
	rm -f $(OBJS)
	rm -f $(NAME)
	make all