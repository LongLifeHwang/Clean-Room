CC = cc
FLAG = -Wall -Wextra -Werror
NAME = clean_room
SOURCE = ./main.c \
		./iot/iot_main.c \
		./iot/ultrasonic_wave.c \
		./utils/ft_split.c 
INC = ./clean_room.h
OBJS = $(SOURCE:.c=.o)
all : $(NAME)

%.o : %.c $(INC)
	$(CC) $(FLAG) -c $< -o $@ -I ./

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

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