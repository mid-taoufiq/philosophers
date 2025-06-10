NAME = philo

HEADER = philosophers.h

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRC =	philosophers.c \
		utils.c

OBJ = ${SRC:.c=.o}

all: ${NAME}
	make clean

${NAME}: ${OBJ}
	cc ${FLAGS} ${OBJ} -o $@

%.o: %.c ${HEADER}
	cc ${FLAGS} -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}