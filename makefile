NAME = philo
NAME_BONUS = philo_bonus

HEADER = philosophers.h
BHEADER = philosophers_bonus.h

FLAGS = -Wall -Wextra -Werror 

SRC =	./mandatory/philosophers.c \
		./mandatory/utils.c \
		./mandatory/utils2.c \
		./mandatory/routine.c \
		./mandatory/monitor.c
BONUS =	./bonus/philosophers_bonus.c \
		./bonus/utils_bonus.c \
		./bonus/utils2_bonus.c \

OBJ = ${SRC:.c=.o}
BOBJ = $(BONUS:.c=.o)

all: ${NAME}
	make clean
bonus: ${NAME_BONUS}
	make clean

${NAME}: ${OBJ}
	cc ${FLAGS} ${OBJ} -o $@
${NAME_BONUS}: ${BOBJ}
	cc ${FLAGS} ${BOBJ} -o $@

mandatory/%.o: mandatory/%.c ./mandatory/philosophers.h
	cc ${FLAGS} -c $< -o $@
bonus/%.o: bonus/%.c ./bonus/philosophers_bonus.h
	cc $(FLAGS) -c $< -o $@

clean:
	rm -rf ${OBJ} ${BOBJ}

fclean: clean
	rm -rf ${NAME} ${NAME_BONUS}

re: fclean ${NAME}