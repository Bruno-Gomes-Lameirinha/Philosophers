TARGET = philo

SRCDIR = src
INCDIR = includes

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -pthread -g

SRC = $(SRCDIR)/philo.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re