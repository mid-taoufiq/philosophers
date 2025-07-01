NAME = philo

HEADER = philosophers.h

FLAGS = -Wall -Wextra -Werror 

SRC =	philosophers.c \
		utils.c \
		utils2.c \
		monitor.c \
		routine.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	cc ${FLAGS} ${OBJ} -o $@

%.o: %.c ${HEADER}
	cc ${FLAGS} -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}