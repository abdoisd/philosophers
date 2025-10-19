SRCS	= main_bonus.c program_bonus.c str_utils_bonus.c utils_bonus.c
OBJS	= ${SRCS:.c=.o}
FLAGS	= -Wall -Wextra -Werror
NAME	= philo_bonus

all: ${NAME}

${NAME} : ${OBJS}
	cc ${OBJS} ${FLAGS} -o ${NAME}

%.o:%.c philo_bonus.h
	cc -c ${FLAGS} $< -o $@

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all
