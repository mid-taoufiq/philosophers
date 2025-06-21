NAME = philo
NAME_BONUS = philo_bonus

HEADER = philosophers.h
BHEADER = philosophers_bonus.h

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRC =	./mandatory/philosophers.c \
		./mandatory/utils.c \
		./mandatory/utils2.c \
		./mandatory/routine.c \
		./mandatory/monitor.c

OBJ = ${SRC:.c=.o}
BOBJ = $(BONUS:.c=.o)

all: ${NAME}
	make clean

${NAME}: ${OBJ}
	cc ${FLAGS} ${OBJ} -o $@

${NAME_BONUS}: ${BOBJ}
	cc ${FLAGS} ${BOBJ} -o $@

mandatory/%.o: mandatory/%.c ./mandatory/philosophers.h
	cc ${FLAGS} -c $< -o $@

bonus/%.o: bonus/%.c ./bonus/philosophers_bonus.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}