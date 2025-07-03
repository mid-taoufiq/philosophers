NAME = philo_bonus

HEADER = philosophers_bonus.h

FLAGS = -Wall -Wextra -Werror

SRC =	philosophers_bonus.c \
		utils_bonus.c \
		utils2_bonus.c \
		utils3_bonus.c \
		routine_bonus.c

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
