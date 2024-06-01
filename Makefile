CC = gcc
FLAG = -Wall -Wextra -Werror
NAME = clean_room
SOURCE = ./main.c \
		./gui_thread.c \
		./iot/dust_check.c \
		./iot/iot_main.c \
		./utils/ft_split.c 
INC = ./clean_room.h
all : $(NAME)

$(NAME): $(SOURCE) $(INC)
	$(CC) -o $(NAME) $(SOURCE) 'pkg-config --cflags --libs gtk+-3.0' -lwiringPi

.PHONY : clean re all

clean :
	rm -f $(NAME)

re :
	rm -f $(NAME)
	make all
